#include "include/scene.h"
#include <iostream>

Scene::Scene(){
	Scene_Objects = vector<Object*>(0,NULL);
	boxes = vector<Box>(0);
}


void Scene::Add(Object* obj){
	Scene_Objects.push_back(obj);
}


void Scene::CreateBox(glm::vec3 &cameraPos,glm::vec3 &cameraFront){
	boxes.push_back(Box(0.5f,0.5f,0.5f,"data/box2.jpg",1.0f,
	glm::vec3(cameraPos.x+cameraFront.x,cameraPos.y+cameraFront.y,cameraPos.z+cameraFront.z),
	cameraFront,glm::vec3(0.0f,0.0f,0.0f),6.f));
	boxes.back().InitRenderData();
	boxes.back().InitTime();
	
	
}
void Scene::InitScene(int last){
    for(uint i=last;i<Scene_Objects.size();i++){
    	Scene_Objects[i]->InitRenderData();
    	Scene_Objects[i]->InitTexture();
    }

}

void Scene::DrawScene(Shader *sh,glm::vec3 &camera_pos, glm::vec3 &camera_front, glm::vec3 &camera_up){
	for(uint i=0;i<Scene_Objects.size();i++){
		Scene_Objects[i]->Render(sh,camera_pos,camera_front,camera_up);
	}
}

void Scene::DrawBoxes(Shader *sh,glm::vec3 &camera_pos, glm::vec3 &camera_front, glm::vec3 &camera_up){
	for(uint i=0;i<boxes.size();i++){
		boxes[i].Render(sh,camera_pos,camera_front,camera_up);
	}
}