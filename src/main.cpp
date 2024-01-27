#include <shader.hpp>
#include <camera.hpp>
#include <rectangle.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

int g_windowSizeX = 800;
int g_windowSizeY = 600;

Camera camera(glm::vec3(0.0f,0.0f,3.0f));
GLfloat lastX = g_windowSizeX / 2.0f;
GLfloat lastY = g_windowSizeY / 2.0f;
GLboolean firstMouse = true;
GLboolean keys[1024];

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,GL_TRUE);
    }

    if(action == GLFW_PRESS)
    {
        keys[key] = true;
    }else if(action == GLFW_RELEASE)
    {
        keys[key] = false;
    }
}

void doMovement()
{
    if(keys[GLFW_KEY_W]){camera.ProcessKeyBoard(FORWARD,deltaTime);}
    if(keys[GLFW_KEY_S]){camera.ProcessKeyBoard(BACKWARD,deltaTime);}
    if(keys[GLFW_KEY_A]){camera.ProcessKeyBoard(LEFT,deltaTime);}
    if(keys[GLFW_KEY_D]){camera.ProcessKeyBoard(RIGHT,deltaTime);}
}

void glfwMouseCallback(GLFWwindow *window, GLdouble xposIn, GLdouble yposIn)
{
    GLfloat xpos = static_cast<GLfloat>(xposIn);
    GLfloat ypos = static_cast<GLfloat>(yposIn);

    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset,yoffset);
}

void glfwScrollCallback(GLFWwindow *window, GLdouble xoffset, GLdouble yoffset)
{
    camera.ProcessMouseScroll(static_cast<GLfloat>(yoffset));
}

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }
    
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);
    glfwSetCursorPosCallback(window,glfwMouseCallback);
    glfwSetScrollCallback(window,glfwScrollCallback);

    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    std::cout << "Render: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version:" << glGetString(GL_VERSION)  << std::endl;
    glEnable(GL_DEPTH_TEST); 

    Shader shader("resources/shaders/vertex.txt","resources/shaders/fragment.txt");
    shader.use();
    Rectangle rectangle{};
    //rectangle.loadTexture("resources/images/container.jpg","jpg",shader);
    //rectangle.loadTexture("resources/images/awesomeface.png","png",shader);

    while (!glfwWindowShouldClose(window))
    {
        // render
        // ------
        GLfloat currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        doMovement(); 

        glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       

        glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (GLfloat)g_windowSizeX / (GLfloat)g_windowSizeY, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("view", view);

        // render boxes
        float angle = 20.0f;
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            angle = 20.0f * glfwGetTime();
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMat4("model", model);
            rectangle.draw();
            
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
