#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
	std::cout << "Failed to read shader file: " << filename << std::endl;
    throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
    std::string vertexShaderSource = get_file_contents(vertexFile);
    std::string fragmentShaderSource = get_file_contents(fragmentFile);
	const char* vertexShaderSourceCStr = vertexShaderSource.c_str();
	const char* fragmentShaderSourceCStr = fragmentShaderSource.c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceCStr, nullptr);
    glCompileShader(vertexShader); // Compile the vertex shader into machine code that the GPU can understand
	errorCheck(vertexShader, GL_COMPILE_STATUS, false, "VERTEX SHADER COMPILATION FAILED");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, nullptr);
    glCompileShader(fragmentShader); // Compile the fragment shader into machine code that the GPU can understand
	errorCheck(fragmentShader, GL_COMPILE_STATUS, false, "FRAGMENT SHADER COMPILATION FAILED");

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID); // link all the shaders together into the final program that will run on the GPU
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
};
void Shader::errorCheck(unsigned int shader, int flag, bool isProgram, const std::string& errorMessage) const {
    int success;
    char infoLog[1024];
    if (isProgram) {
        glGetProgramiv(shader, flag, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER: " << errorMessage << "\n" << infoLog << std::endl;
        }
    }
    else {
        glGetShaderiv(shader, flag, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER: " << errorMessage << "\n" << infoLog << std::endl;
        }
    }
}
void Shader::Activate() const {
    glUseProgram(ID); // Tell OpenGL to use the shader program when rendering objects
}
void Shader::Delete() const {
    glDeleteProgram(ID); // Delete the shader program when it's no longer needed
}