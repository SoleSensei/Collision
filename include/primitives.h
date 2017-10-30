#pragma once
#include "glad.h"
#include <GLFW/glfw3.h>
#include "shader_s.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Parallelepiped{
	// Render state
	Shader shader; 
    GLuint quadVAO;
 public:
	GLfloat width,height,depth;
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 rotation;
	GLfloat velocity;
	GLfloat rot_velocity;
	Parallelepiped(Shader &sh,
				   GLfloat w, GLfloat h, GLfloat d,glm::vec3 pos=glm::vec3(0.0f,0.0f,0.0f),
				   glm::vec3 dir=glm::vec3(0.0f,0.0f,0.0f),glm::vec3 rotation=glm::vec3(0.0f,0.0f,0.0f),
				   GLfloat vel=0.0f, GLfloat rot_vel=0.0f);
	void InitRenderData();
	void Render();
};