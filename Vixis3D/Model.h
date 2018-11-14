#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <map>

#include "Face.h"
#include "Display.h"
#include "Transform.h"
#include "Texture.h"
#include "ModelPart.h"
#include "Material.h"

namespace VIX {
	class Model {
	public:
		Model();
		~Model();

		/*void createCube(double s, const Texture & texture);

		void createSquare(double s, const Texture & texture);*/

		void load(std::string objFile, Texture (*textureLoadFunc)(std::string));

		void draw(Display & display, const Transform & transform);

		std::string getFileName();

		int getTriCount();
	private:
		void clear();

		void loadMaterials(std::string file, Texture(*textureLoadFunc)(std::string));

		std::vector<ModelPart*> parts;
		ModelPart* currentPart;
		std::map<std::string, Material> materials;

		std::vector<Vec3> vertices;
		std::vector<Vec2> uvs;
		std::vector<Vec3> normals;

		std::string fileName;
		int triCount;
	};
}

#endif