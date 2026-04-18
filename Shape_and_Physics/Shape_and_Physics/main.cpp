#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"


#include <stb/stb_image.h>

#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"


/* new window dimention when window is resized */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


// Vertices coordinates
GLfloat vertices[] =
{
    // positions           // colors            // tex coords   // normals

    // base
    -0.5f, 0.0f,  0.5f,    0.83f, 0.70f, 0.44f,   0.0f, 0.0f,   0.0f, -1.0f,  0.0f,
    -0.5f, 0.0f, -0.5f,    0.83f, 0.70f, 0.44f,   0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
     0.5f, 0.0f, -0.5f,    0.83f, 0.70f, 0.44f,   1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
     0.5f, 0.0f,  0.5f,    0.83f, 0.70f, 0.44f,   1.0f, 0.0f,   0.0f, -1.0f,  0.0f,

    // front
    -0.5f, 0.0f,  0.5f,    0.92f, 0.86f, 0.76f,   0.0f, 0.0f,   0.0f,  0.447f,  0.894f,
     0.5f, 0.0f,  0.5f,    0.92f, 0.86f, 0.76f,   1.0f, 0.0f,   0.0f,  0.447f,  0.894f,
     0.0f, 0.8f,  0.0f,    0.92f, 0.86f, 0.76f,   0.5f, 1.0f,   0.0f,  0.447f,  0.894f,

    // right
     0.5f, 0.0f,  0.5f,    0.92f, 0.86f, 0.76f,   0.0f, 0.0f,   0.894f,  0.447f,  0.0f,
     0.5f, 0.0f, -0.5f,    0.92f, 0.86f, 0.76f,   1.0f, 0.0f,   0.894f,  0.447f,  0.0f,
     0.0f, 0.8f,  0.0f,    0.92f, 0.86f, 0.76f,   0.5f, 1.0f,   0.894f,  0.447f,  0.0f,

    // back
     0.5f, 0.0f, -0.5f,    0.92f, 0.86f, 0.76f,   0.0f, 0.0f,   0.0f,  0.447f, -0.894f,
    -0.5f, 0.0f, -0.5f,    0.92f, 0.86f, 0.76f,   1.0f, 0.0f,   0.0f,  0.447f, -0.894f,
     0.0f, 0.8f,  0.0f,    0.92f, 0.86f, 0.76f,   0.5f, 1.0f,   0.0f,  0.447f, -0.894f,

    // left
    -0.5f, 0.0f, -0.5f,    0.92f, 0.86f, 0.76f,   0.0f, 0.0f,  -0.894f,  0.447f,  0.0f,
    -0.5f, 0.0f,  0.5f,    0.92f, 0.86f, 0.76f,   1.0f, 0.0f,  -0.894f,  0.447f,  0.0f,
     0.0f, 0.8f,  0.0f,    0.92f, 0.86f, 0.76f,   0.5f, 1.0f,  -0.894f,  0.447f,  0.0f
};

// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3,
    4, 5, 6,
    7, 8, 9,
    10, 11, 12,
    13, 14, 15
};


// cube vertices and indices
GLfloat cubVertices[] =
{
    // positions           // colors           // tex coords
    -0.25f, -0.25f,  0.25f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     0.25f, -0.25f,  0.25f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
     0.25f,  0.25f,  0.25f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    -0.25f,  0.25f,  0.25f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,

    -0.25f, -0.25f, -0.25f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
     0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
     0.25f,  0.25f, -0.25f,  0.5f, 0.5f, 0.5f,  0.0f, 1.0f,
    -0.25f,  0.25f, -0.25f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f
};

GLuint cubIndices[] =
{
    // front
    0, 1, 2,
    0, 2, 3,
    // right
    1, 5, 6,
    1, 6, 2,
    // back
    5, 4, 7,
    5, 7, 6,
    // left
    4, 0, 3,
    4, 3, 7,
    // top
    3, 2, 6,
    3, 6, 7,
    // bottom
    4, 5, 1,
    4, 1, 0
};

GLfloat planeVertices[] =
{
    // positions             // colors           // tex coords   // normals
    -5.0f, 0.0f, -5.0f,      1.0f, 1.0f, 1.0f,   0.0f, 5.0f,    0.0f, 1.0f, 0.0f,
     5.0f, 0.0f, -5.0f,      1.0f, 1.0f, 1.0f,   5.0f, 5.0f,    0.0f, 1.0f, 0.0f,
     5.0f, 0.0f,  5.0f,      1.0f, 1.0f, 1.0f,   5.0f, 0.0f,    0.0f, 1.0f, 0.0f,
    -5.0f, 0.0f,  5.0f,      1.0f, 1.0f, 1.0f,   0.0f, 0.0f,    0.0f, 1.0f, 0.0f
};

GLuint planeIndices[] =
{
    0, 1, 2,
    0, 2, 3
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

    glEnable(GL_DEPTH_TEST);
    //////////////////////////////////////////////////////////////////////////////
    Shader planeShader("Defualt.vert", "Defualt.frag");

    // creat the vao and then binds it
    VAO PlaneVAO;
    PlaneVAO.Bind();

    //Give the EBO and VBO the indices and the vertices, and generate the vertex buffer and the element buffer
    VBO PlaneVBO(planeVertices, sizeof(planeVertices));
    EBO PlaneEBO(planeIndices, sizeof(planeIndices));

    // link the VBO with the VAO
    PlaneVAO.LinkAtribute(PlaneVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    PlaneVAO.LinkAtribute(PlaneVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    PlaneVAO.LinkAtribute(PlaneVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    PlaneVAO.LinkAtribute(PlaneVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

    // unbind all to prevent accidentally modifycation 
    PlaneVAO.Unbind();
    PlaneVBO.Unbind();
    PlaneEBO.Unbind();

    //////////////////////////////////////////////////////////////////////////////
	Shader lightShader("Light.vert", "Light.frag");

    // creat the vao and then binds it
    VAO VAO2;
    VAO2.Bind();
    
    //Give the EBO and VBO the indices and the vertices, and generate the vertex buffer and the element buffer
    VBO VBO2(cubVertices, sizeof(cubVertices));
    EBO EBO2(cubIndices, sizeof(cubIndices));

    // link the VBO with the VAO
    VAO2.LinkAtribute(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO2.LinkAtribute(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO2.LinkAtribute(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    // unbind all to prevent accidentally modifycation 
    VAO2.Unbind();
    VBO2.Unbind();
    EBO2.Unbind();


    ////////////////////////////////////////////////////////////////////////////////////////////
    // generate the shaders
    Shader shaderprogram("Defualt.vert", "Defualt.frag");
    

    // creat the vao and then binds it
    VAO VAO1;
    VAO1.Bind();

	//Give the EBO and VBO the indices and the vertices, and generate the vertex buffer and the element buffer
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

	// link the VBO with the VAO
    VAO1.LinkAtribute(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    VAO1.LinkAtribute(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAtribute(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.LinkAtribute(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

    // unbind all to prevent accidentally modifycation 
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    //////////////////////////////////////////////////////////////////////////

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(1.5f, 1.5f, 1.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.5f));

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);


	shaderprogram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderprogram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderprogram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderprogram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


    glm::vec3 planePos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 planeModel = glm::mat4(1.0f);
    planeModel = glm::translate(planeModel, planePos);

    planeShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(planeShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(planeModel));
    glUniform4f(glGetUniformLocation(planeShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(planeShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


    // generate the texture
	Texture texture("Brick_Wall.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    texture.TextureUnit(shaderprogram, "tex0", 0);

    Texture planeTexture("Tile.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    planeTexture.TextureUnit(planeShader, "tex1", 1);


	//set up the camera
	Camera camera(1600, 1024, glm::vec3(0.0f, 2.0f, 2.0f));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) // purple
    {
        glClearColor(0.7f, 0.0f, 0.8f, 0.4f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.UpdateCamMatrix(45.0f, 0.1f, 100.0f);

		// activate the shader for the pyramid and bind the texture, then draw the pyramid
        shaderprogram.Activate();
        glUniform3f(glGetUniformLocation(shaderprogram.ID, "camPos"), camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);
		texture.Bind();
        VAO1.Bind();
        camera.camMatrix(shaderprogram, "camMatrix");
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);


		// activate the shader for the light and draw the light
		lightShader.Activate();
        glClearColor(0.7f, 0.0f, 0.8f, 0.4f);
        VAO2.Bind();
        camera.camMatrix(lightShader, "camMatrix");
        glDrawElements(GL_TRIANGLES, sizeof(cubIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);


		// activate the shader for the flat plane and bind the texture, then draw the plane
        planeShader.Activate();
        glUniform3f(glGetUniformLocation(planeShader.ID, "camPos"), camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);
        glClearColor(0.7f, 0.0f, 0.8f, 0.4f);
        planeTexture.Bind();
        PlaneVAO.Bind();
        camera.camMatrix(planeShader, "camMatrix");
        glDrawElements(GL_TRIANGLES, sizeof(planeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    VAO1.Deactivate();
    VBO1.Deactivate();
    EBO1.Deactivate();

    VAO2.Deactivate();
    VBO2.Deactivate();
    EBO2.Deactivate();

    PlaneVAO.Deactivate();
    PlaneVBO.Deactivate();
    PlaneEBO.Deactivate();

	texture.Deactivate();

	shaderprogram.Deactivate();

	lightShader.Deactivate();

    glfwTerminate();
    return 0;
}
