#ifndef QUANTUNGRAPHICSTOOLKIT_SHADER_H
#define QUANTUNGRAPHICSTOOLKIT_SHADER_H

#include <string>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"
#include "logger.h"

class Shader {
public:
	unsigned int id;
	
	Shader(const std::string& vsh, const std::string& fsh) : id(glCreateProgram()){
		unsigned int vertex, fragment;
		int status;
		char infoLog[512];
		
		const char* vCode = vsh.c_str();
		const char* fCode = fsh.c_str();
		
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vCode, nullptr);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);
		if (!status) {
			glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
			std::string error = infoLog;
			log(ERROR, "Failed to compile vertex shader due to error: \n" + error);
		}
		
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fCode, nullptr);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &status);
		if (!status) {
			glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
			std::string error = infoLog;
			log(ERROR, "Failed to compile fragment shader due to error: \n" + error);
			
		}
		
		glAttachShader(id, vertex);
		glAttachShader(id, fragment);
		glLinkProgram(id);
		glGetShaderiv(id, GL_LINK_STATUS, &status);
		if (!status) {
			glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
			std::string error = infoLog;
			log(ERROR, "Failed to link shader program due to error: \n" + error);
		}
		
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	
	void use() const {
		glUseProgram(id);
	}
	
	void setBool(const std::string& loc, bool val) const {
		glUniform1i(glGetUniformLocation(id, loc.c_str()), (int)val);
	}
	
	void setInt(const std::string& loc, int val) const {
		glUniform1i(glGetUniformLocation(id, loc.c_str()), val);
	}
	
	void setFloat(const std::string& loc, float val) const {
		glUniform1f(glGetUniformLocation(id, loc.c_str()), val);
	}
	
	void setVec3f(const std::string& loc, glm::vec3 val) const {
		glUniform3f(glGetUniformLocation(id, loc.c_str()), val.x, val.y, val.z);
	}
	
	void setMat4f(const std::string& loc, glm::mat4 val) const {
		glUniformMatrix4fv(glGetUniformLocation(id, loc.c_str()), 1, GL_FALSE, glm::value_ptr(val));
	}
};


#endif //QUANTUNGRAPHICSTOOLKIT_SHADER_H
