#ifndef QUANTUNGRAPHICSTOOLKIT_RENDERABLECHARACTER_H
#define QUANTUNGRAPHICSTOOLKIT_RENDERABLECHARACTER_H


#include <glm/glm.hpp>
#include "glad/glad.h"

class RenderableCharacter {
public:
	GLuint texId;
	glm::ivec2 size;
	glm::ivec2 bearing;
	GLuint advance;

public:
	RenderableCharacter(GLuint texId, const glm::ivec2& size, const glm::ivec2& bearing, GLuint advance) : texId(texId),
	                                                                                                       size(size),
	                                                                                                       bearing(bearing),
	                                                                                                       advance(advance) {
		
	}
};


#endif //QUANTUNGRAPHICSTOOLKIT_RENDERABLECHARACTER_H
