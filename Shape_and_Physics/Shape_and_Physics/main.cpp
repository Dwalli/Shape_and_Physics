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



float vertices[] = {
        //     Cordiants                             r,    g,     b//
    -0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
     0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
     0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
    -0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
     0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
     0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
};

GLuint indices[] = {
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Lower right triangle
    5, 4, 1 // Upper triangle
};



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


    // generate the shaders
    Shader shaderprogram("Defualt.vert", "Defualt.frag");


    // creat the vao and then binds it
    VAO VAO1;
    VAO1.Bind();

	//Give the EBO and VBO the indices and the vertices, and generate the vertex buffer and the element buffer
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

	// link the VBO with the VAO
    VAO1.LinkAtribute(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAtribute(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // unbind all to prevent accidentally modifycation 
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    GLuint uniID = glGetUniformLocation(shaderprogram.ID, "scale");
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) // purple
    {
        /*set the fram color buffer in RGB values*/
        glClearColor(0.7f, 0.0f, 0.8f, 0.4f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderprogram.Activate();
		glUniform1f(uniID, 0.2f);

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
