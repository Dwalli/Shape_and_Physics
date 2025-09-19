#include "Shader.h"

std::string get_file_contents(const char* filename)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

Shader::Shader(const char* vertex_shader, const char* fragment_shader)
{
    std::string vertexShaderFile = get_file_contents(vertex_shader);
    std::string fragmentShaderFile = get_file_contents(fragment_shader);

    const char* vertexSouce = vertexShaderFile.c_str();
    const char* fragmentSouce = fragmentShaderFile.c_str();


    GLuint vertexShader;  /* create shader object to store the vertex shaders */
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // attach the shader source code to the shader object and compile the shader 
    glShaderSource(vertexShader, 1, &vertexSouce, NULL);
    glCompileShader(vertexShader);



    // same as don with vertex shader but with fragment shader
    GLuint fragmentShader;  /* create shader object to stor the fragment shaders */
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // attach the shader source code to the shader object and compile the shader 
    glShaderSource(fragmentShader, 1, &fragmentSouce, NULL);
    glCompileShader(fragmentShader);


    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);


    // delete old shader object as they are now within the shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

void Shader::Activate()
{

    glUseProgram(ID);

}

void Shader::Deactivate()
{

    glDeleteProgram(ID);

}
