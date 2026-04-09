#version 430 core

layout(triangles) in; // The input primitive type is triangles, which means that the geometry shader will receive three vertices for each primitive.
layout(triangle_strip, max_vertices = 3) out; // The output primitive type is triangle_strip, which means that the geometry shader will output a strip of triangles. The max_vertices = 3 specifies that the maximum number of vertices that can be emitted for each input primitive is 3.

out vec3 crntPos; // The output position of the vertex in clip space, which is used to determine where the vertex will be rendered on the screen.
out vec3 Normal;
out vec3 color;
out vec2 texCoord;

in DATA // The input from the vertex shader, which includes the normal, color, and texture coordinates for each vertex of the triangle.
{
	vec3 Normal;
	vec3 color;
	vec2 texCoord;
	mat4 projection;
} data_in[]; //data_in is an array of the input data for each vertex of the triangle.

void main()
{
	gl_Position = data_in[0].projection * gl_in[0].gl_Position;
    crntPos = gl_in[0].gl_Position.xyz;
    Normal = data_in[0].Normal;
    color = data_in[0].color;
    texCoord = data_in[0].texCoord;
    EmitVertex();

    gl_Position = data_in[1].projection * gl_in[1].gl_Position;
    crntPos = gl_in[1].gl_Position.xyz;
    Normal = data_in[1].Normal;
    color = data_in[1].color;
    texCoord = data_in[1].texCoord;
    EmitVertex();

    gl_Position = data_in[2].projection * gl_in[2].gl_Position;
    crntPos = gl_in[2].gl_Position.xyz;
    Normal = data_in[2].Normal;
    color = data_in[2].color;
    texCoord = data_in[2].texCoord;
    EmitVertex();

    EndPrimitive();

}