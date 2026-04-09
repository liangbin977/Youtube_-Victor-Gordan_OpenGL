#pragma once
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>
#include <iostream>

std::string get_file_contents(const char* filename);

class Shader {
public:
	unsigned int ID;
	Shader(const char* vertexShader, const char* fragmentShader, const char* geometryShader);
	void Activate() const;
	void Delete() const;
	void errorCheck(unsigned int shader, int flag, bool isProgram, const std::string& errorMessage) const;
};



