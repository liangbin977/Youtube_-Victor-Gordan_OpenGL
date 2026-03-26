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
uniform vec3 camPos; // get the camera position from the main function

vec4 pointLight() {
    vec3 lightVec = lightPos - crntPos; // calculate the vector from the current position to the light position
    float dist = length(lightVec); // calculate the distance from the current position to the light position
    float a = 2.0f;
    float b = 0.7f;
    float decay = 1.0f / (a * dist * dist + b * dist + 1.0f); // calculate the decay factor based on the distance and the attenuation coefficients
    
    float ambient = 0.2; // set the ambient lighting to a constant value

    vec3 norm = normalize(Normal); //normalize the normal vector and get a unit vector that points in the same direction as the normal
    vec3 lightDir = normalize(lightVec); //set the light direction by subtracting the current position from the light position and normalizing it
    float diff = max(dot(norm, lightDir), 0.0f); //use the value of cosine to express the intensity of the light
    
    float specularStrength = 0.5f;    // set the strength of the specular highlight
    vec3 viewDir = normalize(camPos - crntPos);    // calculate the view direction by subtracting the current position from the camera position and normalizing it
    vec3 reflectDir = reflect(-lightDir, norm);    // calculate the reflection direction by reflecting the light direction around the normal vector
    float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 32);    // calculate the specular highlight using the dot product of the view direction and the reflection direction, raised to a power to control the shininess of the surface
    float specular = specularStrength * specAmount;    // calculate the final specular contribution by multiplying the strength of the specular highlight by the calculated value

    return (texture(texSlot, TexCoord) * (diff * decay + ambient) + texture(texSlot1, TexCoord).r * specular * decay) * lightColor;   //rememer to use multiply
};
vec4 direcLight() {

    float ambient = 0.2; // set the ambient lighting to a constant value

    vec3 norm = normalize(Normal); //normalize the normal vector and get a unit vector that points in the same direction as the normal
    vec3 lightDir = normalize(vec3(1.0f, 1.0f, 0.0f)); //set the light direction by subtracting the current position from the light position and normalizing it
    float diff = max(dot(norm, lightDir), 0.0f); //use the value of cosine to express the intensity of the light
    
    float specularStrength = 0.5f;    // set the strength of the specular highlight
    vec3 viewDir = normalize(camPos - crntPos);    // calculate the view direction by subtracting the current position from the camera position and normalizing it
    vec3 reflectDir = reflect(-lightDir, norm);    // calculate the reflection direction by reflecting the light direction around the normal vector
    float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 32);    // calculate the specular highlight using the dot product of the view direction and the reflection direction, raised to a power to control the shininess of the surface
    float specular = specularStrength * specAmount;    // calculate the final specular contribution by multiplying the strength of the specular highlight by the calculated value

    return (texture(texSlot, TexCoord) * (diff + ambient) + texture(texSlot1, TexCoord).r * specular) * lightColor;   //rememer to use multiply
};
vec4 spotLight() {
    float outerCosine = 0.90f;
    float innerCosine = 0.95f;

    float ambient = 0.2; // set the ambient lighting to a constant value

    vec3 norm = normalize(Normal); //normalize the normal vector and get a unit vector that points in the same direction as the normal
    vec3 lightDir = normalize(lightPos - crntPos); //set the light direction by subtracting the current position from the light position and normalizing it
    float diff = max(dot(norm, lightDir), 0.0f); //use the value of cosine to express the intensity of the light
    
    float specularStrength = 0.5f;    // set the strength of the specular highlight
    vec3 viewDir = normalize(camPos - crntPos);    // calculate the view direction by subtracting the current position from the camera position and normalizing it
    vec3 reflectDir = reflect(-lightDir, norm);    // calculate the reflection direction by reflecting the light direction around the normal vector
    float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 32);    // calculate the specular highlight using the dot product of the view direction and the reflection direction, raised to a power to control the shininess of the surface
    float specular = specularStrength * specAmount;    // calculate the final specular contribution by multiplying the strength of the specular highlight by the calculated value
    
    float angle = dot(-lightDir, vec3(0.0f, -1.0f, 0.0f)); // calculate the angle between the light direction and the spotlight direction (assuming the spotlight is pointing in the negative z-axis)
    float inten = clamp((angle - outerCosine) / (innerCosine - outerCosine), 0.0f, 1.0f); // calculate the intensity of the spotlight based on the angle and the inner and outer cone angles

    return (texture(texSlot, TexCoord) * (diff * inten + ambient) + texture(texSlot1, TexCoord).r * specular * inten) * lightColor;   //rememer to use multiply
};
void main(){
    FragColor = spotLight();
}