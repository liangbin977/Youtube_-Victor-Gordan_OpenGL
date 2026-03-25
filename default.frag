#version 430 core
//fragmentShader根据位置权重对vertex封闭起来的区域内的每一个片段进行着色，输出一个颜色值。每个片段的颜色值由纹理采样、光照计算和其他因素决定。
out vec4 FragColor; // the output color of the fragment shader, which will be passed to the next stage in the pipeline (e.g., blending, depth testing, etc.)

in vec3 ourColor;
in vec2 TexCoord; //get the texture coord from the vertex shader
in vec3 Normal; //get the normal from the vertex shader
in vec3 crntPos; //get the current position from the vertex shader

uniform sampler2D texSlot; //get the texture unit from the main function
uniform sampler2D texSlot1; //get the second texture unit from the main function
uniform vec4 lightColor; // get the light color from the main function
uniform vec3 lightPos; // get the light position from the main function
uniform vec3 cameraPos; // get the camera position from the main function

void main()
{
    float ambient = 0.2; // set the ambient lighting to a constant value

    vec3 norm = normalize(Normal); //normalize the normal vector and get a unit vector that points in the same direction as the normal
    vec3 lightDir = normalize(lightPos - crntPos); //set the light direction by subtracting the current position from the light position and normalizing it
    float diff = max(dot(norm, lightDir), 0.0f); //calculate the angle between the normal and the light direction using the dot product, and take the maximum of that value and 0.0 to ensure that it doesn't go negative (i.e., if the light is behind the surface, it won't contribute to the lighting)
    
    float specularStrength = 0.5f; // set the strength of the specular highlight
    vec3 viewDir = normalize(cameraPos - crntPos); // calculate the view direction by subtracting the current position from the camera position and normalizing it
    vec3 reflectDir = reflect(-lightDir, norm); // calculate the reflection direction by reflecting the light direction around the normal vector
    float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 16); // calculate the specular highlight using the dot product of the view direction and the reflection direction, raised to a power to control the shininess of the surface
    float specular = specularStrength * specAmount; // calculate the final specular contribution by multiplying the strength of the specular highlight by the calculated value

    FragColor = texture(texSlot, TexCoord) * lightColor * (diff + ambient) + texture(texSlot1, TexCoord).r * specular; //rememer to use multiply
};