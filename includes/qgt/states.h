#ifndef QUANTUNGRAPHICSTOOLKIT_STATES_H
#define QUANTUNGRAPHICSTOOLKIT_STATES_H

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

static glm::mat4 projection = glm::ortho(0.0F, 0.0F, 0.0F, 0.0F);

void setProjection(glm::mat4 val) {
	projection = val;
}

glm::mat4 getProjection() {
	return projection;
}

#endif //QUANTUNGRAPHICSTOOLKIT_STATES_H
