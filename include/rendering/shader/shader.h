#pragma once

#include <glad/glad.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <enginemath/vec3.hpp>
#include <enginemath/vec4.hpp>

struct Shader {
public:
	// Program ID
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragPath) {
		std::string vertexCode;
		std::string fragCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			// Open the shader files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragPath);
			std::stringstream vShaderStream, fShaderStream;

			// Read file buffer contents into stream
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();

			// Convert streams into strings
			vertexCode = vShaderStream.str();
			fragCode = fShaderStream.str();
		}

		catch (std::ifstream::failure e) {
			std::cout << "Error: Shader file(s) not readsuccessfully" << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragCode.c_str();

		// Compile + Link Shaders
		unsigned int vertex, frag;
		int success;
		char infoLog[512];

		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "Error: Vertex Shader Compilation\n" << infoLog << std::endl;
		}

		// Fragment Shader
		frag = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(frag, 1, &vShaderCode, NULL);
		glCompileShader(frag);

		glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(frag, 512, NULL, infoLog);
			std::cout << "Error: Fragment Shader Compilation\n" << infoLog << std::endl;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, frag);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "Error: Could not link the shaders together\n" << infoLog << std::endl;
		}

		glDeleteShader(vertex);
		glDeleteShader(frag);
	}


	void use() const {
		glUseProgram(ID);
	}

	void setBool(const std::string& name, bool value);
};