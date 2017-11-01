#pragma once
#include "glad.h"
#include <GLFW/glfw3.h>

#include "shader_s.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//use virtual functions!!!!!!!!!

class Object{
	
 public:

  	virtual void InitRenderData()=0;
  	virtual void InitTexture()=0;
  	virtual void Render(Shader *sh,glm::vec3 &camera_pos, glm::vec3 &camera_front, glm::vec3 &camera_up)=0;


};
class Box: public Object{
	// Render state
	GLuint texture;
	GLuint quadVAO;
	GLfloat angle;
	GLfloat time;
	const char* texture_name;
	GLfloat text_scale;
 public:
	GLfloat width,height,depth;
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 rotation;
	GLfloat velocity;
	GLfloat rot_velocity;
	Box();
	Box(GLfloat w, GLfloat h, GLfloat d, const char * text_name,GLfloat sc,
				   glm::vec3 pos=glm::vec3(0.0f,0.0f,0.0f),
				   glm::vec3 dir=glm::vec3(0.0f,0.0f,0.0f),
				   glm::vec3 rotation=glm::vec3(0.0f,0.0f,0.0f),
				   GLfloat vel=0.0f, GLfloat rot_vel=0.0f);

	virtual void InitRenderData();
	virtual void InitTexture();
	virtual void Render(Shader *sh,glm::vec3 &camera_pos, glm::vec3 &camera_front, glm::vec3 &camera_up);
	void InitTime();
};


class Plane: public Object{
	GLuint texture;
	GLuint quadVAO;
	GLfloat angle;
	const char* texture_name;
	GLfloat text_scale;
 public:
  	//glm::vec3 normal;
  	GLfloat width;
  	GLfloat height;
  	glm::vec3 position;
  	glm::vec3 rotation;


  	Plane(GLfloat w, GLfloat h , const char * text_name,GLfloat sc,
  		  glm::vec3 pos,glm::vec3 rot,GLfloat a);
  	virtual void InitRenderData();
    virtual void InitTexture();
    virtual void Render(Shader *sh,glm::vec3 &camera_pos, glm::vec3 &camera_front, glm::vec3 &camera_up);
};