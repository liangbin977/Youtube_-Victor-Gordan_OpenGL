#version 430 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Normals (not necessarily normalized)
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture Coordinates
layout (location = 3) in vec2 aTex;


// no need to out crntPos, because the geometry shader will calculate the current positions automatically.
// out vec3 crntPos;
out DATA
{
	vec3 Normal;
	vec3 color;
	vec2 texCoord;
	mat4 projection;
} data_out; //data_out is the output data for each vertex of the triangle.



// Imports the camera matrix
uniform mat4 cameraMatrix;
// Imports the transformation matrices
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;


void main()
{
	gl_Position = model * translation * rotation * scale  * vec4(aPos, 1.0f);
	data_out.Normal = aNormal;
	data_out.color = aColor;
	data_out.texCoord = mat2(0, -1, 1, 0) * aTex;
	data_out.projection = cameraMatrix;
}