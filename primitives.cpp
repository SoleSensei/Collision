
#include "include/primitives.h"

Parallelepiped::Parallelepiped(Shader &sh,GLfloat w, GLfloat h, GLfloat d,
				   glm::vec3 pos,glm::vec3 dir,glm::vec3 rot,GLfloat vel,GLfloat rot_vel):shader(sh){

	width = w;
	height = h;
	depth = d;
	direction = dir;
	position = pos;
	rotation = rot;
	velocity = vel;
	rot_velocity = rot_vel;
}


void Parallelepiped::InitRenderData(){
	// Configure VAO/VBO
    GLuint VBO;
    GLfloat vertices[] = {
        // positions          // texture coords
        -width/2, -height/2, -depth/2,  0.0f, 0.0f,
         width/2, -height/2, -depth/2,  1.0f, 0.0f,
         width/2,  height/2, -depth/2,  1.0f, 1.0f,
         width/2,  height/2, -depth/2,  1.0f, 1.0f,
        -width/2,  height/2, -depth/2,  0.0f, 1.0f,
        -width/2, -height/2, -depth/2,  0.0f, 0.0f,

        -width/2, -height/2,  depth/2,  0.0f, 0.0f,
         width/2, -height/2,  depth/2,  1.0f, 0.0f,
         width/2,  height/2,  depth/2,  1.0f, 1.0f,
         width/2,  height/2,  depth/2,  1.0f, 1.0f,
        -width/2,  height/2,  depth/2,  0.0f, 1.0f,
        -width/2, -height/2,  depth/2,  0.0f, 0.0f,

        -width/2,  height/2,  depth/2,  1.0f, 0.0f,
        -width/2,  height/2, -depth/2,  1.0f, 1.0f,
        -width/2, -height/2, -depth/2,  0.0f, 1.0f,
        -width/2, -height/2, -depth/2,  0.0f, 1.0f,
        -width/2, -height/2,  depth/2,  0.0f, 0.0f,
        -width/2,  height/2,  depth/2,  1.0f, 0.0f,

         width/2,  height/2,  depth/2,  1.0f, 0.0f,
     	 width/2,  height/2, -depth/2,  1.0f, 1.0f,
         width/2, -height/2, -depth/2,  0.0f, 1.0f,
         width/2, -height/2, -depth/2,  0.0f, 1.0f,
         width/2, -height/2,  depth/2,  0.0f, 0.0f,
         width/2,  height/2,  depth/2,  1.0f, 0.0f,

        -width/2, -height/2, -depth/2,  0.0f, 1.0f,
         width/2, -height/2, -depth/2,  1.0f, 1.0f,
         width/2, -height/2,  depth/2,  1.0f, 0.0f,
         width/2, -height/2,  depth/2,  1.0f, 0.0f,
        -width/2, -height/2,  depth/2,  0.0f, 0.0f,
        -width/2, -height/2, -depth/2,  0.0f, 1.0f,

        -width/2,  height/2, -depth/2,  0.0f, 1.0f,
         width/2,  height/2, -depth/2,  1.0f, 1.0f,
         width/2,  height/2,  depth/2,  1.0f, 0.0f,
         width/2,  height/2,  depth/2,  1.0f, 0.0f,
        -width/2,  height/2,  depth/2,  0.0f, 0.0f,
        -width/2,  height/2, -depth/2,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
      // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //load texture here
}


void Parallelepiped::Render(){
	// Prepare transformations
    this->shader.use();
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 model;
    projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.1f, 100.0f);
    view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));
    glBindVertexArray(this->quadVAO);
    model = glm::translate(model,position);
    model = glm::translate(model,direction*0.5f*(float)glfwGetTime());
    if(rotation!=glm::vec3(0.0f,0.0f,0.0f))
    	model = glm::rotate(model,(float)glfwGetTime(), rotation);
    // pass transformation matrices to the shader
    this->shader.setMat4("projection", projection);
    this->shader.setMat4("view", view);
    this->shader.setMat4("model", model);

    //add texture handle

    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}