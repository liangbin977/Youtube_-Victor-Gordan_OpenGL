#version 430 core
layout(location = 0) in vec3 aPos;
out vec3 texCoord;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	vec4 pos = projection * view * vec4(aPos, 1.0);
	// having z equal to w causes the depth to be 1.0, which is the farthest depth value, so the skybox will always be rendered behind all other objects
	gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
	//flip the z coordinate to make the skybox render correctly
	texCoord = vec3(aPos.x, aPos.y, -aPos.z);
}