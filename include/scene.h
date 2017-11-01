#pragma once
#include "primitives.h"
#include <vector>

using std::vector;
class Scene{
	vector<Object *> Scene_Objects;
	vector<Box>	boxes;
 public:
	void Add(Object *obj);
	void CreateBox(glm::vec3 &pos,glm::vec3 &dir);
	Scene();
	void DrawBoxes(Shader *sh,glm::vec3 &camera_pos, glm::vec3 &camera_front, glm::vec3 &camera_up);
	void InitScene(int last = 0);
	void DrawScene(Shader *sh,glm::vec3 &camera_pos, glm::vec3 &camera_front, glm::vec3 &camera_up);

};