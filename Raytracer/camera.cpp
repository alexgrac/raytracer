#include "camera.h"
#include "utils.h"

#include <geometric.hpp>

Camera::Camera(glm::vec3 lookFrom, glm::vec3 lookAt, glm::vec3 up, float vfov, float aspect) {
	glm::vec3 u, v, w;
	float theta = vfov * M_PI / 180;
	float halfHeight = tan(theta / 2);
	float halfWidth = aspect * halfHeight;
	_origin = lookFrom;
	w = glm::normalize(lookFrom - lookAt);
	u = glm::normalize(glm::cross(up, w));
	v = glm::cross(w, u);

	_lowerLeft = _origin - halfWidth * u - halfHeight * v - w;
	_horizontal = 2 * halfWidth * u;
	_vertical = 2 * halfHeight * v;
}
