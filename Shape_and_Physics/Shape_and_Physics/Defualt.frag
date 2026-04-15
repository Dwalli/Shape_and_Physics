#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoords;
in vec3 normal;
in vec3 currentPos;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
    //ambient lighting, gives a little base light so the object is never fully black.
    float ambient = 0.2f;

    // diffuse lighting, lights surfaces that face the light.
    float diffuseStrength = 0.3f;
    vec3 obNormal = normalize(normal);
    vec3 lightDirection = normalize(lightPos - currentPos);
    float diffuseLight = max(dot(obNormal, lightDirection), 0.0f) * diffuseStrength;

    //specular creates the shiny highlight.
    float specularStrength = 0.6f;
    vec3 viewDirection = normalize(camPos - currentPos);
    vec3 reflectDir = reflect(-lightDirection, obNormal);
    float specularAmount = pow(max(dot(viewDirection, reflectDir), 0.0f), 90.0f);
    float specular = specularStrength * specularAmount;

    float lighting = diffuseLight + ambient + specular;
    float simpleLighting = diffuseLight + ambient;

    FragColor = texture(tex0, texCoords) * lightColor * lighting;
}