
#include "include/primitives.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

Box::Box(){
    time=0.0;
    width=0.5f;
    height=0.5f;
    text_scale=1.0f;
    texture=0;
    depth=0.5f;
    direction=glm::vec3(0.0f,0.0f,-1.0f);
    position=glm::vec3(0.0f,0.0f,0.0f);
    rotation=glm::vec3(0.0f,0.0f,0.0f);
    velocity=1.0f;
    rot_velocity=0.0f;

}
Box::Box(GLfloat w, GLfloat h, GLfloat d,
         const char * text_name,GLfloat sc,glm::vec3 pos,glm::vec3 dir,
         glm::vec3 rot,GLfloat vel,GLfloat rot_vel){
    time=0.0;
    texture_name = text_name;
    text_scale=sc;
    texture=0;
	width = w;
	height = h;
	depth = d;
	direction = dir;
	position = pos;
	rotation = rot;
	velocity = vel;
	rot_velocity = rot_vel;
}

void Box::InitTime(){
    time = (float)glfwGetTime();
}
void Box::InitRenderData(){
	// Configure VAO/VBO
    GLuint VBO;
    GLfloat vertices[] = {
        // positions          // texture coords
        -width/2, -height/2, -depth/2,  0.0f, 0.0f,
         width/2, -height/2, -depth/2,  text_scale, 0.0f,
         width/2,  height/2, -depth/2,  text_scale, text_scale,
         width/2,  height/2, -depth/2,  text_scale, text_scale,
        -width/2,  height/2, -depth/2,  0.0f, text_scale,
        -width/2, -height/2, -depth/2,  0.0f, 0.0f,

        -width/2, -height/2,  depth/2,  0.0f, 0.0f,
         width/2, -height/2,  depth/2,  text_scale, 0.0f,
         width/2,  height/2,  depth/2,  text_scale, text_scale,
         width/2,  height/2,  depth/2,  text_scale, text_scale,
        -width/2,  height/2,  depth/2,  0.0f, text_scale,
        -width/2, -height/2,  depth/2,  0.0f, 0.0f,

        -width/2,  height/2,  depth/2,  text_scale, 0.0f,
        -width/2,  height/2, -depth/2,  text_scale, text_scale,
        -width/2, -height/2, -depth/2,  0.0f, text_scale,
        -width/2, -height/2, -depth/2,  0.0f, text_scale,
        -width/2, -height/2,  depth/2,  0.0f, 0.0f,
        -width/2,  height/2,  depth/2,  text_scale, 0.0f,

         width/2,  height/2,  depth/2,  text_scale, 0.0f,
     	 width/2,  height/2, -depth/2,  text_scale, text_scale,
         width/2, -height/2, -depth/2,  0.0f, text_scale,
         width/2, -height/2, -depth/2,  0.0f, text_scale,
         width/2, -height/2,  depth/2,  0.0f, 0.0f,
         width/2,  height/2,  depth/2,  text_scale, 0.0f,

        -width/2, -height/2, -depth/2,  0.0f, text_scale,
         width/2, -height/2, -depth/2,  text_scale, text_scale,
         width/2, -height/2,  depth/2,  text_scale, 0.0f,
         width/2, -height/2,  depth/2,  text_scale, 0.0f,
        -width/2, -height/2,  depth/2,  0.0f, 0.0f,
        -width/2, -height/2, -depth/2,  0.0f, text_scale,

        -width/2,  height/2, -depth/2,  0.0f, text_scale,
         width/2,  height/2, -depth/2,  text_scale, text_scale,
         width/2,  height/2,  depth/2,  text_scale, 0.0f,
         width/2,  height/2,  depth/2,  text_scale, 0.0f,
        -width/2,  height/2,  depth/2,  0.0f, 0.0f,
        -width/2,  height/2, -depth/2,  0.0f, text_scale
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


}

void Box::InitTexture(){
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(texture_name, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}
void Box::Render(Shader *sh,glm::vec3 &camera_pos, glm::vec3 &camera_front, glm::vec3 &camera_up){
	// Prepare transformations
    glBindTexture(GL_TEXTURE_2D, this->texture);
    sh->use();
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 model;
    projection = glm::perspective(glm::radians(45.0f), (float)1366 / (float)768, 0.1f, 100.0f);
    view = glm::lookAt(camera_pos, camera_pos+camera_front, camera_up);
    glBindVertexArray(this->quadVAO);
    model = glm::translate(model,direction*velocity*((float)glfwGetTime()-time));
    model = glm::translate(model,position);
    if(rotation!=glm::vec3(0.0f,0.0f,0.0f))
    	model = glm::rotate(model,(float)glfwGetTime()-time, rotation);
    // pass transformation matrices to the shader
    sh->setMat4("projection", projection);
    sh->setMat4("view", view);
    sh->setMat4("model", model);

    //add texture handle

    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}


Plane::Plane(GLfloat w, GLfloat h ,const char * text_name, GLfloat sc, glm::vec3 pos,glm::vec3 rot,GLfloat a){
    //normal = norm;
    texture_name=text_name;
    text_scale=sc;
    width = w;
    height = h;
    position = pos;
    rotation = rot;
    angle = a;
}

void Plane::InitRenderData(){
    GLuint VBO;
    GLfloat vertices[] = {
        // positions          // texture coords
        -width/2, 0.0f, -height/2,  0.0f, text_scale,
         width/2, 0.0f, -height/2,  text_scale, text_scale,
         width/2, 0.0f,  height/2,  text_scale, 0.0f,
         width/2, 0.0f,  height/2,  text_scale, 0.0f,
        -width/2, 0.0f,  height/2,  0.0f, 0.0f,
        -width/2, 0.0f, -height/2,  0.0f, text_scale,
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
}

void Plane::InitTexture(){
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(texture_name, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Plane::Render(Shader *sh,glm::vec3 &camera_pos, glm::vec3 &camera_front, glm::vec3 &camera_up){
    // Prepare transformations
    glBindTexture(GL_TEXTURE_2D, this->texture);



    sh->use();
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 model;
    projection = glm::perspective(glm::radians(45.0f), (float)1366 / (float)768, 0.1f, 100.0f);
    view = glm::lookAt(camera_pos, camera_pos+camera_front, camera_up);
    glBindVertexArray(this->quadVAO);
    model = glm::translate(model,position);
    if(rotation!=glm::vec3(0.0f,0.0f,0.0f))
        model = glm::rotate(model,glm::radians(angle), rotation);
    // pass transformation matrices to the shader
    sh->setMat4("projection", projection);
    sh->setMat4("view", view);
    sh->setMat4("model", model);

    //add texture handle

    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}