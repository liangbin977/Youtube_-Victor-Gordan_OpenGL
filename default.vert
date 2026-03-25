#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 aNormal;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 crntPos;

uniform mat4 model;
uniform mat4 cameraMatrix;

void main(){
    crntPos = vec3(model * vec4(aPos, 1.0f)); // this is the position of the vertex in world space, used for lighting calculations
    gl_Position = cameraMatrix * vec4(crntPos, 1.0f);
    ourColor = aColor;
    TexCoord = texCoord;
    Normal = aNormal;

};