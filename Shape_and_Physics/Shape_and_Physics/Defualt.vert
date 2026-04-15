#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

out vec3 color;
out vec2 texCoords; 
out vec3 normal;
out vec3 currentPos;

// control the scale of the vertices
uniform float scale;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
    currentPos = vec3(model * vec4(aPos, 1.0f));
    //gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);   // whatever we set gl_Position to will be used as the output of the vertex shader.
    gl_Position = camMatrix * vec4(currentPos, 1.0);
    color = aColor;
    texCoords = aTex;
    normal = mat3(transpose(inverse(model))) * aNormal;
}