#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <stb/stb_image.h>

#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

/* new window dimention when window is resized */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


float vertices[] = {
	// Positions        // Colors (RGB)     // Texture Coords (UV)
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Bottom left
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Bottom right
     0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // Top right
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f  // Top left
};

GLuint indices[] = {
    0, 1, 2,  // First triangle (bottom right)
    0, 2, 3   // Second triangle (top left)
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
    VAO1.LinkAtribute(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAtribute(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAtribute(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    // unbind all to prevent accidentally modifycation 
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    GLuint uniID = glGetUniformLocation(shaderprogram.ID, "scale");
    
    //Texturs
	int widthImage, heightImage, numColChanels;
    stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("Brick_Wall.jpg", &widthImage, &heightImage, &numColChanels, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint uniTex0 = glGetUniformLocation(shaderprogram.ID, "tex0");
	shaderprogram.Activate();
	glUniform1i(uniTex0, 0);



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) // purple
    {
        /*set the fram color buffer in RGB values*/
        glClearColor(0.7f, 0.0f, 0.8f, 0.4f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderprogram.Activate();
		glUniform1f(uniID, 0.5f);

        glBindTexture(GL_TEXTURE_2D, texture);

        //Bind VAO so openGL know when to use it
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    VAO1.Deactivate();
    VBO1.Deactivate();
    EBO1.Deactivate();
	glDeleteTextures(1, &texture);
	shaderprogram.Deactivate();

    glfwTerminate();
    return 0;
}
