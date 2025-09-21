#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

/* new window dimention when window is resized */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


int main(void)
{
    /* Initialize the library */
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  /* For this to work on mac uncomment this code */


    GLFWwindow* window;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1600, 1024, "Shape and Physics", NULL, NULL);

    if (!window)
    {
        std::cout << "Failed to creat GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    gladLoadGL();


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        std::cout << "Failed to Load GLAD" << std::endl;
        return -1;

    }


     /* The size of the rendering window */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    /* New verts for square */

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    /*The indices for the square*/
    GLuint indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };


    Shader shaderprogram("Defualt.vert", "Defualt.frag");

    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(0, VBO1);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();




    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) // purple
    {
        /*set the fram color buffer in RGB values*/
        glClearColor(0.7f, 0.0f, 0.8f, 0.4f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderprogram.Activate();

        //Bind VAO so openGL know when to use it
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    VAO1.Deactivate();
    VBO1.Deactivate();
    EBO1.Deactivate();
	shaderprogram.Deactivate();

    glfwTerminate();
    return 0;
}
