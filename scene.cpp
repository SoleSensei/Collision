#include "include/scene.h"


void Scene::Add(Object* obj){
	Scene_Objects.push_back(obj);
}
void Scene::InitScene(){
    for(uint i=0;i<Scene_Objects.size();i++){
    	Scene_Objects[i]->InitRenderData();
    	Scene_Objects[i]->InitTexture();
    }
}

void Scene::DrawScene(glm::vec3 camera_pos, glm::vec3 camera_front, glm::vec3 camera_up){
	for(uint i=0;i<Scene_Objects.size();i++){
		Scene_Objects[i]->Render(camera_pos,camera_front,camera_up);
	}
}