#version 430 core
//输入的图元类型是glDrawArrays(GL_TRIANGLES)决定的，不能修改为其他类型，否则会导致渲染错误。
layout(triangles) in;
//输出图元默认是按照输入图元类型的基础上进行修改的，这里修改为line_strip，表示输出的图元类型是线段。max_vertices = 6表示每个输入图元最多可以输出6个顶点。
layout(line_strip, max_vertices = 6) out;

in DATA
{
	vec3 Normal;
	vec3 color;
	vec2 texCoord;
	mat4 projection;
} data_in[];
//以下是针对一个图元（一个三角形）的处理
{
	gl_Position = data_in[0].projection * gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = data_in[0].projection * (gl_in[0].gl_Position + 0.01f * vec4(data_in[0].Normal, 0.0f));
	EmitVertex();
	EndPrimitive();

	gl_Position = data_in[1].projection * gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = data_in[1].projection * (gl_in[1].gl_Position + 0.01f * vec4(data_in[0].Normal, 0.0f));	
	EmitVertex();
	EndPrimitive();

	gl_Position = data_in[2].projection * gl_in[2].gl_Position;
	EmitVertex();
	gl_Position = data_in[2].projection * (gl_in[2].gl_Position + 0.01f * vec4(data_in[0].Normal, 0.0f));
	EmitVertex();
	EndPrimitive();
}