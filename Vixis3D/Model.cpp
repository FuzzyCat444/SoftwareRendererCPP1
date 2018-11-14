#include "Model.h"
#include "Color.h"
#include "Vertex.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <xutility>

namespace VIX {
	Model::Model() {

	}

	Model::~Model() {
	}

	//void Model::createCube(double s, const Texture & texture) {
	//	clear();

	//	s /= 2.0;

	//	int i = 0;
	//	Vec3 v1(-s, -s, s);
	//	Vec3 v2(s, -s, s);
	//	Vec3 v3(s, s, s);
	//	Vec3 v4(-s, s, s);
	//	Vec2 uv1(0.0, 0.0);
	//	Vec2 uv2(1.0, 0.0);
	//	Vec2 uv3(1.0, 1.0);
	//	Vec2 uv4(0.0, 1.0);

	//	vertices.push_back(Vertex(v1, uv1));
	//	vertices.push_back(Vertex(v2, uv2));
	//	vertices.push_back(Vertex(v3, uv3));
	//	vertices.push_back(Vertex(v4, uv4));
	//	faces.push_back(Face(i, i + 1, i + 2, Color::RED));
	//	faces.push_back(Face(i, i + 2, i + 3, Color::RED));

	//	i += 4;
	//	v1.z *= -1;
	//	v2.z *= -1;
	//	v3.z *= -1;
	//	v4.z *= -1;

	//	vertices.push_back(Vertex(v1, uv1));
	//	vertices.push_back(Vertex(v2, uv2));
	//	vertices.push_back(Vertex(v3, uv3));
	//	vertices.push_back(Vertex(v4, uv4));
	//	faces.push_back(Face(i, i + 1, i + 2, Color::RED));
	//	faces.push_back(Face(i, i + 2, i + 3, Color::RED));

	//	i += 4;
	//	std::swap(v1.z, v1.x);
	//	std::swap(v2.z, v2.x);
	//	std::swap(v3.z, v3.x);
	//	std::swap(v4.z, v4.x);

	//	vertices.push_back(Vertex(v1, uv1));
	//	vertices.push_back(Vertex(v2, uv2));
	//	vertices.push_back(Vertex(v3, uv3));
	//	vertices.push_back(Vertex(v4, uv4));
	//	faces.push_back(Face(i, i + 1, i + 2, Color::RED));
	//	faces.push_back(Face(i, i + 2, i + 3, Color::RED));

	//	i += 4;
	//	v1.x *= -1;
	//	v2.x *= -1;
	//	v3.x *= -1;
	//	v4.x *= -1;

	//	vertices.push_back(Vertex(v1, uv1));
	//	vertices.push_back(Vertex(v2, uv2));
	//	vertices.push_back(Vertex(v3, uv3));
	//	vertices.push_back(Vertex(v4, uv4));
	//	faces.push_back(Face(i, i + 1, i + 2, Color::RED));
	//	faces.push_back(Face(i, i + 2, i + 3, Color::RED));

	//	i += 4;
	//	std::swap(v1.x, v1.y);
	//	std::swap(v2.x, v2.y);
	//	std::swap(v3.x, v3.y);
	//	std::swap(v4.x, v4.y);

	//	vertices.push_back(Vertex(v1, uv1));
	//	vertices.push_back(Vertex(v2, uv2));
	//	vertices.push_back(Vertex(v3, uv3));
	//	vertices.push_back(Vertex(v4, uv4));
	//	faces.push_back(Face(i, i + 1, i + 2, Color::RED));
	//	faces.push_back(Face(i, i + 2, i + 3, Color::RED));

	//	i += 4;
	//	v1.y *= -1;
	//	v2.y *= -1;
	//	v3.y *= -1;
	//	v4.y *= -1;

	//	vertices.push_back(Vertex(v1, uv1));
	//	vertices.push_back(Vertex(v2, uv2));
	//	vertices.push_back(Vertex(v3, uv3));
	//	vertices.push_back(Vertex(v4, uv4));
	//	faces.push_back(Face(i, i + 1, i + 2, Color::RED));
	//	faces.push_back(Face(i, i + 2, i + 3, Color::RED));

	//	//// Back side
	//	//vertices.push_back(Vertex(Vec3(-s, -s, -s), Vec2(0.0, 0.0)));
	//	//vertices.push_back(Vertex(Vec3(s, -s, -s), Vec2(texture.getWidth(), 0.0)));
	//	//vertices.push_back(Vertex(Vec3(s, s, -s), Vec2(texture.getWidth(), texture.getHeight())));
	//	//vertices.push_back(Vertex(Vec3(-s, s, -s), Vec2(0.0, texture.getHeight())));

	//	//// Front side
	//	//vertices.push_back(Vertex(Vec3(-s, -s, s), Vec2(0.0, 0.0)));
	//	//vertices.push_back(Vertex(Vec3(s, -s, s), Vec2(texture.getWidth(), 0.0)));
	//	//vertices.push_back(Vertex(Vec3(s, s, s), Vec2(texture.getWidth(), texture.getHeight())));
	//	//vertices.push_back(Vertex(Vec3(-s, s, s), Vec2(0.0, texture.getHeight())));

	//	//// Right side
	//	//vertices.push_back(Vertex(Vec3(s, -s, -s), Vec2(0.0, 0.0)));
	//	//vertices.push_back(Vertex(Vec3(s, -s, s), Vec2(texture.getWidth(), 0.0)));
	//	//vertices.push_back(Vertex(Vec3(s, s, -s), Vec2(texture.getWidth(), texture.getHeight())));
	//	//vertices.push_back(Vertex(Vec3(-s, s, -s), Vec2(0.0, texture.getHeight())));

	//	//// Left side
	//	//vertices.push_back(Vertex(Vec3(-s, -s, s), Vec2(0.0, 0.0)));
	//	//vertices.push_back(Vertex(Vec3(s, -s, s), Vec2(texture.getWidth(), 0.0)));
	//	//vertices.push_back(Vertex(Vec3(s, s, s), Vec2(texture.getWidth(), texture.getHeight())));
	//	//vertices.push_back(Vertex(Vec3(-s, s, s), Vec2(0.0, texture.getHeight())));

	//	//// Front
	//	//faces.push_back(Face(0, 1, 2, Color::RED));
	//	//faces.push_back(Face(0, 2, 3, Color::RED));

	//	//// Right
	//	//faces.push_back(Face(1, 5, 6, Color::GREEN));
	//	//faces.push_back(Face(1, 2, 6, Color::GREEN));

	//	//// Back
	//	//faces.push_back(Face(4, 5, 6, Color::RED));
	//	//faces.push_back(Face(4, 6, 7, Color::RED));

	//	//// Left
	//	//faces.push_back(Face(0, 4, 7, Color::GREEN));
	//	//faces.push_back(Face(0, 7, 3, Color::GREEN));

	//	//// Top
	//	//faces.push_back(Face(3, 2, 6, Color::BLUE));
	//	//faces.push_back(Face(3, 6, 7, Color::BLUE));

	//	//// Bottom
	//	//faces.push_back(Face(0, 1, 5, Color::BLUE));
	//	//faces.push_back(Face(0, 5, 4, Color::BLUE));

	//	this->texture = texture;
	//}

	/*void Model::createSquare(double s, const Texture & texture)
	{
		clear();

		s /= 2.0;

		vertices.push_back(Vertex(Vec3(-s, -s, 0.0), Vec2(0.0, 0.0)));
		vertices.push_back(Vertex(Vec3(s, -s, 0.0), Vec2(1.0, 0.0)));
		vertices.push_back(Vertex(Vec3(s, s, 0.0), Vec2(1.0, 1.0)));
		vertices.push_back(Vertex(Vec3(-s, s, 0.0), Vec2(0.0, 1.0)));

		faces.push_back(Face(0, 1, 2, Color::RED));
		faces.push_back(Face(0, 2, 3, Color::GREEN));

		this->texture = texture;
	}*/

	// Crappy .obj loader
	void Model::load(std::string objFile, Texture(*textureLoadFunc)(std::string)) {
		clear();
		fileName = objFile;

		std::istringstream removeExt(objFile);
		std::string name;
		std::getline(removeExt, name, '.');

		std::ifstream ifs(objFile);
		std::string line;

		// Create empty part with no texture
		currentPart = new ModelPart();

		while(std::getline(ifs, line)) {
			std::istringstream iss(line);
			std::string token;
			std::getline(iss, token, ' ');

			if (token == "mtllib") {
				std::string materialLib;

				if (std::getline(iss, materialLib, ' ')) {
					if (textureLoadFunc != nullptr) loadMaterials(materialLib, textureLoadFunc);
				}
			}
			else if (token == "usemtl") {
				std::string materialName;

				// Create new model part if old one has been filled
				if (currentPart->faces.size() > 0) {
					parts.push_back(currentPart);
					currentPart = new ModelPart();
				}
				// Set material information of model part
				if (std::getline(iss, materialName, ' ')) {
					if (materials.find(materialName) != materials.end()) {
						currentPart->material = materials[materialName];
					}
				}
			}
			else if (token == "v") {
				std::string x, y, z;

				if (std::getline(iss, x, ' ') && std::getline(iss, y, ' ') && std::getline(iss, z, ' ')) {
					vertices.push_back(Vec3(std::stod(x), std::stod(y), std::stod(z)));
				}
			}
			else if (token == "vt") {
				std::string u, v;

				if (std::getline(iss, u, ' ') && std::getline(iss, v, ' ')) {
					uvs.push_back(Vec2(std::stod(u), std::stod(v)));
				}
			}
			else if (token == "vn") {
				std::string x, y, z;

				if (std::getline(iss, x, ' ') && std::getline(iss, y, ' ') && std::getline(iss, z, ' ')) {
					normals.push_back(Vec3(std::stod(x), std::stod(y), std::stod(z)));
				}
			}
			else if (token == "f") {
				std::string v1, v2, v3;
				if (std::getline(iss, v1, ' ') && std::getline(iss, v2, ' ') && std::getline(iss, v3, ' ')) {
					std::istringstream v1StringStream(v1);
					std::istringstream v2StringStream(v2);
					std::istringstream v3StringStream(v3);
					std::string vp1, vt1, vn1, vp2, vt2, vn2, vp3, vt3, vn3;

					if (std::getline(v1StringStream, vp1, '/') && std::getline(v1StringStream, vt1, '/') && std::getline(v1StringStream, vn1, '/') &&
						std::getline(v2StringStream, vp2, '/') && std::getline(v2StringStream, vt2, '/') && std::getline(v2StringStream, vn2, '/') &&
						std::getline(v3StringStream, vp3, '/') && std::getline(v3StringStream, vt3, '/') && std::getline(v3StringStream, vn3, '/')) {
						Vertex v1(vertices[std::stoi(vp1) - 1], uvs[std::stoi(vt1) - 1], normals[std::stoi(vn1) - 1]);
						Vertex v2(vertices[std::stoi(vp2) - 1], uvs[std::stoi(vt2) - 1], normals[std::stoi(vn2) - 1]);
						Vertex v3(vertices[std::stoi(vp3) - 1], uvs[std::stoi(vt3) - 1], normals[std::stoi(vn3) - 1]);
						v1.uv.y = 1.0 - v1.uv.y;
						v2.uv.y = 1.0 - v2.uv.y;
						v3.uv.y = 1.0 - v3.uv.y;
						v1.uv.x *= currentPart->material.texture.getWidth();
						v2.uv.x *= currentPart->material.texture.getWidth();
						v3.uv.x *= currentPart->material.texture.getWidth();
						v1.uv.y *= currentPart->material.texture.getHeight();
						v2.uv.y *= currentPart->material.texture.getHeight();
						v3.uv.y *= currentPart->material.texture.getHeight();
						Face face(v1, v2, v3);

						currentPart->faces.push_back(face);
						triCount++;
					}
				}
			}
		}

		parts.push_back(currentPart);

		vertices.clear();
		uvs.clear();
		normals.clear();

		ifs.close();
	}

	void Model::draw(Display & display, const Transform & trans) {
		for (auto it = parts.begin(); it != parts.end(); it++) {
			display.setTexture((*it)->material.texture);
			std::vector<Face>& partFaces = (*it)->faces;
			for (auto it2 = partFaces.begin(); it2 != partFaces.end(); it2++) {
				const Face& face = *it2;

				Vertex v1 = face.v1;
				Vertex v2 = face.v2;
				Vertex v3 = face.v3;

				v1.xyz = trans.transform3(v1.xyz, false);
				v2.xyz = trans.transform3(v2.xyz, false);
				v3.xyz = trans.transform3(v3.xyz, false);

				v1.normal = trans.transform3(v1.normal, true);
				v2.normal = trans.transform3(v2.normal, true);
				v3.normal = trans.transform3(v3.normal, true);

				Vec3 surfaceNormal = trans.transform3(face.surfaceNormal, true);

				display.drawTriangle(v1, v2, v3, surfaceNormal);
			}
		}
	}

	std::string Model::getFileName()
	{
		return fileName;
	}

	int Model::getTriCount()
	{
		return triCount;
	}

	void Model::clear()
	{
		triCount = 0;
		parts.clear();
		vertices.clear();
		uvs.clear();
		normals.clear();
		materials.clear();
	}

	// Crappy material parser
	void Model::loadMaterials(std::string file, Texture(*textureLoadFunc)(std::string))
	{
		std::string line;
		std::ifstream ifs(file);
		
		std::string currentMaterial;

		while (std::getline(ifs, line)) {
			std::istringstream iss(line);
			std::string token;
			std::getline(iss, token, ' ');

			if (token == "newmtl") {
				std::string materialName;

				if (std::getline(iss, materialName, ' ')) {
					currentMaterial = materialName;
				}
			}
			else if (token == "map_Kd") {
				std::string textureFile;

				if (std::getline(iss, textureFile, ' ')) {
					Material mat;
					mat.texture = textureLoadFunc(textureFile);
					materials[currentMaterial] = mat;
				}
			}
		}

		ifs.close();
	}
}