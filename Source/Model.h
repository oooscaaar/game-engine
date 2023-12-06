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
	std::list<Mesh*> meshes;
	//std::vector<unsigned> textures;
};

