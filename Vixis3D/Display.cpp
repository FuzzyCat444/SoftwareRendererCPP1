#include "Display.h"

#include <random>
#include <utility>
#include <cmath>
#include <xutility>

#include "MathFunctions.h"
#include "Edge.h"

namespace VIX {
	Display::Display(int width, int height, double fovAngle) : width(width), height(height), aspectRatio(static_cast<double>(width) / height), pixelCount(width * height), pixels(new uint32_t[pixelCount]), color(255, 255, 255), zBuffer(new double[pixelCount]),
	zNear(1.0), zFar(1000.0), texture(), clippingEnabled(true) {
		worldToScreenScale.setScale3(Vec3(height * 0.5, -height * 0.5, 1.0));
		worldToScreenTranslate.setTranslate3(Vec3(width * 0.5, height * 0.5, 0.0));
		worldToScreenScale.chain(&worldToScreenTranslate);
		perspective.setPerspective3(fovAngle);
		perspectiveDivide = perspective.getPerspectiveDivide();
		enableLighting();
	}

	Display::~Display() {
		delete zBuffer;
		for (auto it = pointLights.begin(); it != pointLights.end(); it++) {
			delete (*it).second;
		}
		for (auto it = directionalLights.begin(); it != directionalLights.end(); it++) {
			delete (*it).second;
		}
	}

	void Display::clear() {
		std::fill_n(pixels, pixelCount, 0);
		std::fill_n(zBuffer, pixelCount, 100.0);
	}

	void Display::setColor(const Color & color) {
		this->color = color;
	}

	void Display::setTexture(const Texture & texture) {
		this->texture = texture;
	}

	void Display::drawTriangle(const Vertex & v1, const Vertex & v2, const Vertex & v3, const Vec3& surfaceNormal) {
		Vertex nv1 = camera.transformVertex(v1);
		Vertex nv2 = camera.transformVertex(v2);
		Vertex nv3 = camera.transformVertex(v3);

		Vec3 nSurfaceNormal = camera.transformPoint(surfaceNormal, true);

		if (triangleVisible(nv1, nv2, nv3, nSurfaceNormal)) {
			Clipper::Result clipResult = nearClipper.clip(nv1, nv2, nv3);

			if (clipResult == Clipper::UNCLIPPED || !clippingEnabled) {
				drawIndividualTriangle(nv1, nv2, nv3);
			}
			else if (clipResult == Clipper::CLIPPED_1) {
				auto tri = nearClipper.getTri1();
				drawIndividualTriangle(tri[0], tri[1], tri[2]);
			}
			else if (clipResult == Clipper::CLIPPED_2) {
				auto tri1 = nearClipper.getTri1();
				auto tri2 = nearClipper.getTri2();
				drawIndividualTriangle(tri1[0], tri1[1], tri1[2]);
				drawIndividualTriangle(tri2[0], tri2[1], tri2[2]);
			}
		}
	}

	bool Display::triangleVisible(const Vertex & v1, const Vertex & v2, const Vertex & v3, const Vec3& surfaceNormal)
	{
		bool visible = true;

		// Back face culling
		Vec3 camPos = camera.getPosition();
		Vec3 toCam(-v1.xyz.x, -v1.xyz.y, -v1.xyz.z);
		if (toCam.dot(surfaceNormal) < 0) {
			visible = false;
		}

		return visible;
	}

	void Display::drawIndividualTriangle(const Vertex & v1, const Vertex & v2, const Vertex & v3)
	{
		Vertex v1Orig(v1);
		Vertex v2Orig(v2);
		Vertex v3Orig(v3);
		Vertex vt1(worldToScreenScale.transform3(perspective.transform3(v1.xyz, false), false), v1.uv);
		Vertex vt2(worldToScreenScale.transform3(perspective.transform3(v2.xyz, false), false), v2.uv);
		Vertex vt3(worldToScreenScale.transform3(perspective.transform3(v3.xyz, false), false), v3.uv);

		// Sort vertices
		if (vt1.xyz.y > vt2.xyz.y) {
			std::swap(vt1, vt2);
			std::swap(v1Orig, v2Orig);
		}
		if (vt2.xyz.y > vt3.xyz.y) {
			std::swap(vt2, vt3);
			std::swap(v2Orig, v3Orig);
		}
		if (vt1.xyz.y > vt2.xyz.y) {
			std::swap(vt1, vt2);
			std::swap(v1Orig, v2Orig);
		}

		double flatBottomHeight = vt2.xyz.y - vt1.xyz.y;
		double flatTopHeight = vt3.xyz.y - vt2.xyz.y;

		double m = (vt3.xyz.x - vt1.xyz.x) / (vt3.xyz.y - vt1.xyz.y);
		double inter = vt1.xyz.x + m * (vt2.xyz.y - vt1.xyz.y);

		if (vt2.xyz.x < inter) scanTriangle(vt2, vt1, vt3, v2Orig, v1Orig, v3Orig, flatBottomHeight, TriType::FB);
		else scanTriangle(vt3, vt1, vt2, v3Orig, v1Orig, v2Orig, flatBottomHeight, TriType::FB);

		if (vt2.xyz.x < inter) scanTriangle(vt2, vt3, vt1, v2Orig, v3Orig, v1Orig, flatTopHeight, TriType::FT);
		else scanTriangle(vt1, vt3, vt2, v1Orig, v3Orig, v2Orig, flatTopHeight, TriType::FT);
	}

	void Display::scanTriangle(const Vertex & left, const Vertex & middle, const Vertex & right, const Vertex & leftOrig, const Vertex & middleOrig, const Vertex & rightOrig, double h, TriType type)
	{
		/*
			Triangle variable setup for each kind of triangle (flat bottom and flat top)
		*/
		double yReal;		// The actual scanline y value (projected but not converted to screen coords)
		double pixelSize;	// The size of one pixel in projected screen units
		int sy;				// The starting scanline y value
		int ey;				// The ending scanline y value (inclusive)
		double ldenom;		// Denominator of inverse slope of left triangle edge
		double rdenom;		// Denominator of inverse slope of right triangle edge
		double ml;			// Inverse slope of left triangle edge
		double mr;			// Inverse slope of right triangle edge
		double c;			// The difference between the starting y and the middle vertex y (to initialize start and end x values with slopes)
		double sx;			// The starting x value of the scanline
		double ex;			// The ending x value of the scanline
		int py;				// The number of pixels from the beginning of the array to the current row
		int rowInc;			// The width increase per row of pixels (negative or positive)

		switch (type) {
		case TriType::FB:
			sy = fastRound(middle.xyz.y);
			ey = fastRound(middle.xyz.y + h * type) - 1;

			if (ey - sy < 0) return;

			sy = std::max(0, sy);
			ey = std::min(height - 1, ey);
			break;
		case TriType::FT:
			sy = fastRound(middle.xyz.y) - 1;
			ey = fastRound(middle.xyz.y + h * type);

			if (sy - ey < 0) return;

			sy = std::min(height - 1, sy);
			ey = std::max(0, ey);
			break;
		default:
			break;
		}

		ldenom = (middle.xyz.y - left.xyz.y);
		rdenom = (middle.xyz.y - right.xyz.y);

		ml = (middle.xyz.x - left.xyz.x) * type / (ldenom != 0 ? ldenom : 1);
		mr = (middle.xyz.x - right.xyz.x) * type / (rdenom != 0 ? rdenom : 1);

		c = (sy - middle.xyz.y + 0.5) * type;
		sx = middle.xyz.x + c * ml;
		ex = middle.xyz.x + c * mr;
		pixelSize = 2.0 / height;
		yReal = 1.0 - 2.0 * (sy + 0.5) / height;

		py = sy * width;
		rowInc = width * type;

		int pixelLoc;

		double ambientLight = lightingEnabled ? 0.05 : 1.0;

		// Accumulates all the light coming from every PointLight/DirectionalLight and hitting these vertices
		Vec3 accumLightLeft(ambientLight, ambientLight, ambientLight);
		Vec3 accumLightRight(ambientLight, ambientLight, ambientLight);
		Vec3 accumLightMiddle(ambientLight, ambientLight, ambientLight);
		if (lightingEnabled) {
			for (auto it = pointLights.begin(); it != pointLights.end(); it++) {
				const PointLight & light = *(*it).second;
				double brLeft = light.getBrightness(leftOrig.normal, leftOrig.xyz, &camera.getTransform());
				double brRight = light.getBrightness(rightOrig.normal, rightOrig.xyz, &camera.getTransform());
				double brMiddle = light.getBrightness(middleOrig.normal, middleOrig.xyz, &camera.getTransform());
				Vec3 lightCol = light.getColor();

				accumLightLeft.x += brLeft * lightCol.x;
				accumLightLeft.y += brLeft * lightCol.y;
				accumLightLeft.z += brLeft * lightCol.z;

				accumLightRight.x += brRight * lightCol.x;
				accumLightRight.y += brRight * lightCol.y;
				accumLightRight.z += brRight * lightCol.z;

				accumLightMiddle.x += brMiddle * lightCol.x;
				accumLightMiddle.y += brMiddle * lightCol.y;
				accumLightMiddle.z += brMiddle * lightCol.z;
			}
			for (auto it = directionalLights.begin(); it != directionalLights.end(); it++) {
				const DirectionalLight & light = *(*it).second;
				double brLeft = light.getBrightness(leftOrig.normal, &camera.getTransform());
				double brRight = light.getBrightness(rightOrig.normal, &camera.getTransform());
				double brMiddle = light.getBrightness(middleOrig.normal, &camera.getTransform());
				Vec3 lightCol = light.getColor();

				accumLightLeft.x += brLeft * lightCol.x;
				accumLightLeft.y += brLeft * lightCol.y;
				accumLightLeft.z += brLeft * lightCol.z;

				accumLightRight.x += brRight * lightCol.x;
				accumLightRight.y += brRight * lightCol.y;
				accumLightRight.z += brRight * lightCol.z;

				accumLightMiddle.x += brMiddle * lightCol.x;
				accumLightMiddle.y += brMiddle * lightCol.y;
				accumLightMiddle.z += brMiddle * lightCol.z;
			}
		}

		leftEdge.set(middleOrig, leftOrig, accumLightMiddle, accumLightLeft, yReal, pixelSize * -type, Edge::Axis::Y, perspectiveDivide);
		rightEdge.set(middleOrig, rightOrig, accumLightMiddle, accumLightRight, yReal, pixelSize * -type, Edge::Axis::Y, perspectiveDivide);
		Vertex a;
		Vertex b;
		Vec3 col1;
		Vec3 col2;

		// Actual rasterization
		int scanlineCount = (ey - sy) * type + 1;
		for (int y = 0; y < scanlineCount; y++) {
			int sxi = fastRound(sx);
			int exi = fastRound(ex) - 1;

			sxi = std::max(0, sxi);
			exi = std::min(width - 1, exi);

			double xlOrig;
			double xrOrig;

			double zl = leftEdge.getZ();
			double zr = rightEdge.getZ();

			double sxReal = aspectRatio * (2.0 * sx / width - 1.0);
			double sxpReal = aspectRatio * (2.0 * (sxi + 0.5) / width - 1.0);
			double exReal = aspectRatio * (2.0 * ex / width - 1.0);

			xlOrig = zl * perspectiveDivide * sxReal;
			xrOrig = zr * perspectiveDivide * exReal;

			double ul = leftEdge.getU();
			double vl = leftEdge.getV();
			double ur = rightEdge.getU();
			double vr = rightEdge.getV();

			col1.x = leftEdge.getR(); col1.y = leftEdge.getG(); col1.z = leftEdge.getB();
			col2.x = rightEdge.getR(); col2.y = rightEdge.getG(); col2.z = rightEdge.getB();

			scanEdge.set(Vertex(Vec3(xlOrig, 0.0, zl), Vec2(ul, vl)), Vertex(Vec3(xrOrig, 0.0, zr), Vec2(ur, vr)), col1, col2, sxpReal, pixelSize, Edge::Axis::X, perspectiveDivide);
			for (int x = sxi; x <= exi; x++) {
				pixelLoc = py + x;

				// Interpolated z and uv values
				double zp = scanEdge.getZ();
				double u = scanEdge.getU();
				double v = scanEdge.getV();

				// Interpolated light color values
				double lr = scanEdge.getR();
				double lg = scanEdge.getG();
				double lb = scanEdge.getB();
				if (lr > 1.0) lr = 1.0;
				if (lg > 1.0) lg = 1.0;
				if (lb > 1.0) lb = 1.0;

				int pixel;
				if (!texture.isNull()) {
					pixel = texture.getPixelAt(u, v);
				}
				else {
					pixel = color.combined();
				}

				if (zp < zBuffer[pixelLoc] && (pixel & 0xff)) {
					zBuffer[pixelLoc] = zp;

					int pixR = pixel >> 24 & 0xff;
					int pixG = pixel >> 16 & 0xff;
					int pixB = pixel >> 8 & 0xff;
					pixR *= lr;
					pixG *= lg;
					pixB *= lb;
					pixel = pixR << 24 | pixG << 16 | pixB << 8;

					pixels[pixelLoc] = pixel;
				}
				scanEdge.step();
			}
			sx += ml;
			ex += mr;
			py += rowInc;
			leftEdge.step();
			rightEdge.step();
		}
	}

	void Display::addPointLight(PointLight* light, std::string name) {
		pointLights[name] = light;
	}

	PointLight* Display::getPointLight(std::string name) {
		return pointLights[name];
	}

	PointLight* Display::removePointLight(std::string name) {
		PointLight* light = pointLights[name];
		pointLights.erase(name);
		return light;
	}

	void Display::addDirectionalLight(DirectionalLight* light, std::string name) {
		directionalLights[name] = light;
	}

	DirectionalLight* Display::getDirectionalLight(std::string name) {
		return directionalLights[name];
	}

	DirectionalLight* Display::removeDirectionalLight(std::string name) {
		DirectionalLight* light = directionalLights[name];
		directionalLights.erase(name);
		return light;
	}

	void Display::enableLighting()
	{
		lightingEnabled = true;
	}

	void Display::disableLighting()
	{
		lightingEnabled = false;
	}

	// Not used yet
	double Display::normalizeZ(double z) const
	{
		return (z - zNear) / (zFar - zNear);
	}

	uint32_t ** Display::getPixelsPointer() {
		return &pixels;
	}

	Camera & Display::getCamera()
	{
		return camera;
	}
}
