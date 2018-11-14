#ifndef DISPLAY_H
#define DISPLAY_H

#include <cstdint>
#include <map>
#include <string>
#include <utility>

#include "Color.h"
#include "Vec2.h"
#include "Transform.h"
#include "Texture.h"
#include "Vertex.h"
#include "Edge.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Clipper.h"
#include "Camera.h"

namespace VIX {
	class Display
	{
	public:
		Display(int width, int height, double fovAngle);
		~Display();

		void clear();

		void setColor(const Color & color);
		void setTexture(const Texture & texture);
		void drawTriangle(const Vertex & v1, const Vertex & v2, const Vertex & v3, const Vec3& surfaceNormal);

		void addPointLight(PointLight* light, std::string name);
		PointLight* getPointLight(std::string name);
		PointLight* removePointLight(std::string name);

		void addDirectionalLight(DirectionalLight* light, std::string name);
		DirectionalLight* getDirectionalLight(std::string name);
		DirectionalLight* removeDirectionalLight(std::string name);

		void enableLighting();
		void disableLighting();

		uint32_t ** getPixelsPointer();

		Camera& getCamera();
	private:
		enum TriType {
			FB = 1,
			FT = -1
		};

		bool triangleVisible(const Vertex & v1, const Vertex & v2, const Vertex & v3, const Vec3& surfaceNormal);

		void drawIndividualTriangle(const Vertex & v1, const Vertex & v2, const Vertex & v3);

		void scanTriangle(const Vertex & left, const Vertex & middle, const Vertex & right, const Vertex & leftOrig, const Vertex & middleOrig, const Vertex & rightOrig, double h, TriType type);

		double normalizeZ(double z) const;

		int width;
		int height;
		double aspectRatio;
		int pixelCount;
		Color color;
		uint32_t * pixels;
		double * zBuffer;

		Transform worldToScreenScale;
		Transform worldToScreenTranslate;
		Transform perspective;
		double perspectiveDivide;
		double zNear;
		double zFar;
		Clipper nearClipper;
		bool clippingEnabled;
		Camera camera;

		Texture texture;

		Edge leftEdge;
		Edge rightEdge;
		Edge scanEdge;

		std::map<std::string, PointLight*> pointLights;
		std::map<std::string, DirectionalLight*> directionalLights;
		bool lightingEnabled;
	};
}

#endif

