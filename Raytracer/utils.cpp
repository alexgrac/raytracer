#include "utils.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx\norm.hpp>

namespace rtrax {

	glm::vec3 randomInUnitSphere() {
		glm::vec3 p;
		do {
			p = float(2.0) * glm::vec3(rand01(), rand01(), rand01()) - glm::vec3(1, 1, 1);
		} while (glm::length2(p) >= 1.0);

		return p;
	}

	float rand01() {
		return (float(rand()) / RAND_MAX);
	}

};