#include "include/glad.h"
#include <GLFW/glfw3.h>
//#define STB_IMAGE_IMPLEMENTATION
//#include "include/stb_image.h"
#include "include/scene.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "include/shader_s.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void left_click(GLFWwindow* window,int button, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

//camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  0.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);


Scene scene;

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;


// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main(){
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", glfwGetPrimaryMonitor(), nullptr);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window,left_click); 
    glfwSetCursorPosCallback(window,mouse_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glEnable(GL_DEPTH_TEST);
    // build and compile shader program
    

    //Compile shaders

    Shader objshader("shaders/object.vs","shaders/object.fs");
    Shader boxshader("shaders/boxshader.vs","shaders/boxshader.fs");

    //Create Scene
	Box p(0.2f,0.7f,0.2f,"data/box.jpg",1.0f,glm::vec3(-0.5f,0.5f,0.0f));
	scene.Add(&p);
    Box p2(0.5f,0.2f,0.5f,"data/box2.jpg",1.0f,glm::vec3(0.5f,0.5f,0.0f),glm::vec3(0.0f,0.1f,0.0f),glm::vec3(0.5f,1.0f,0.0f));
    scene.Add(&p2);
    Plane floor(10.0f,10.0f,"data/floor.jpg",5.0f,glm::vec3(0.0f,-1.0f,0.0f),glm::vec3(1.0f,0.0f,0.0f),0.0f);
    scene.Add(&floor);
    Plane leftwall(10.0f,10.0f,"data/wall.jpeg",1.0f,glm::vec3(-5.0f,4.0f,0.0f),glm::vec3(0.0f,0.0f,-1.0f),90.0f);
    scene.Add(&leftwall);
    Plane rightwall(10.0f,10.0f,"data/wall.jpeg",1.0f,glm::vec3(5.0f,4.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f),90.0f);
    scene.Add(&rightwall);
    Plane backwall(10.0f,10.0f,"data/787.jpg",1.0f,glm::vec3(0.0f,4.0f,-5.0f),glm::vec3(1.0f,0.0f,0.0f),90.f);
    scene.Add(&backwall);
    scene.InitScene();
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
    	float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.DrawScene(&objshader,cameraPos,cameraFront,cameraUp);
        scene.DrawBoxes(&boxshader,cameraPos,cameraFront,cameraUp);


        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5 * deltaTime; 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos -= glm::normalize(cameraUp) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += glm::normalize(cameraUp) * cameraSpeed;
}

void left_click(GLFWwindow* window,int button, int action, int mods){
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS){
		scene.CreateBox(cameraPos,cameraFront);
	}
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}
