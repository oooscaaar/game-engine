#pragma once
#include "Application.h"
#include "Mesh.h"



class Model
{
	public:

		Model();
		~Model();
		void Draw(const char* filePath);


	private:
		std::vector<Mesh*> meshes;
		std::vector<unsigned int> textures;
};

