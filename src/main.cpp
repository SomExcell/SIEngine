#include <window.hpp>
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

void fps()
{
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    double currentTime = glfwGetTime();
    nbFrames++;
    if ( currentTime - lastTime >= 0.0 ){ // If last prinf() was more than 1 sec ago
        // printf and reset timer
        std::cout << 1000.0/(double)nbFrames << "ms/frame\n";
        nbFrames = 0;
        lastTime += 1.0;
    }
}


int main(void)
{
    Window window{};

    Shader shader("resources/shaders/vertex.txt","resources/shaders/fragment.txt");
    shader.use();
    Rectangle rectangle{};
    //rectangle.loadTexture("resources/images/container.jpg","jpg",shader);
    //rectangle.loadTexture("resources/images/awesomeface.png","png",shader);

    while (!window.closed())
    {
        // render
        // ------
        GLfloat currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        doMovement(); 

        rectangle.setColor(0.2f,0.2f,sin(glfwGetTime()));
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
        window.swapBuffers();
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
