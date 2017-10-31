#pragma once
#include "primitives.h"
#include <vector>

using std::vector;
class Scene{
	vector<Object *> Scene_Objects;	
 public:
	void Add(Object *obj);
	Scene(){
		Scene_Objects = vector<Object*>(0,NULL);
	}
	void InitScene();
	void DrawScene(glm::vec3 camera_pos, glm::vec3 camera_front, glm::vec3 camera_up);

};