#pragma once

#include <glad/glad.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <enginemath/vec2.hpp>
#include <enginemath/vec3.hpp>
#include <enginemath/vec4.hpp>
#include <enginemath/mat4.hpp>

struct Shader {
public:
	// Program ID
	unsigned int ID = 0;

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
			std::cout << "Error: Shader file(s) not read successfully" << std::endl;
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
		frag = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(frag, 1, &fShaderCode, NULL);
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

	~Shader() { glDeleteProgram(ID); }

	void use() const { glUseProgram(ID); }

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader&& other) noexcept : ID(other.ID) {
		other.ID = 0;
	}

	Shader& operator=(Shader&& other) noexcept {
		if (this != &other) {
			glDeleteProgram(ID);
			ID = other.ID;
			other.ID = 0;
		}
		return *this;
	}

	void setBool(const std::string& name, bool value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value); }

	void setInt(const std::string& name, int value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
	
	void setFloat(const std::string& name, float value) {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }

	void setVec2(const std::string& name, enginemath::Vec2 vector) {
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, vector.data); }

	void setVec3(const std::string& name, enginemath::Vec3 vector) {
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, vector.elements); }

	void setVec4(const std::string& name, enginemath::Vec4 vector) {
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, vector.elements); }

	void setMat4(const std::string& name, enginemath::Mat4 matrix) {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, matrix.m[0]); }

};