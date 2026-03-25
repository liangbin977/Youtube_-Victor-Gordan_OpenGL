#version 430 core

out vec4 FragColor; // the output color of the fragment shader, which will be passed to the next stage in the pipeline (e.g., blending, depth testing, etc.)

in vec3 ourColor;
in vec2 TexCoord; //get the texture coord from the vertex shader
in vec3 Normal; //get the normal from the vertex shader
in vec3 crntPos; //get the current position from the vertex shader

uniform sampler2D texSlot; //get the texture unit from the main function
uniform vec4 lightColor; // get the light color from the main function
uniform vec3 lightPos; // get the light position from the main function

void main()
{
    float ambient = 0.2; // set the ambient lighting to a constant value

    vec3 norm = normalize(Normal); //normalize the normal vector
    vec3 lightDir = normalize(lightPos - crntPos); //set the light direction by subtracting the current position from the light position and normalizing it
    float diff = max(dot(norm, lightDir), 0.0f); //calculate the diffuse lighting using the dot product of the normal and light direction
    FragColor = texture(texSlot, TexCoord) * lightColor * (diff + ambient);
};