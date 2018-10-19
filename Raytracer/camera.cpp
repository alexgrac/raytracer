#include "camera.h"
#include "utils.h"

#include <geometric.hpp>

Camera::Camera(glm::vec3 lookFrom, glm::vec3 lookAt, glm::vec3 up, float vfov, float aspect, float aperture, float focusDist) {
	_lensRadius = aperture / 2;
	float theta = vfov * M_PI / 180;
	float halfHeight = tan(theta / 2);
	float halfWidth = aspect * halfHeight;
	_origin = lookFrom;
	_w = glm::normalize(lookFrom - lookAt);
	_u = glm::normalize(glm::cross(up, _w));
	_v = glm::cross(_w, _u);

	_lowerLeft = _origin - halfWidth * focusDist * _u - halfHeight * focusDist * _v - focusDist * _w;
	_horizontal = 2 * halfWidth * focusDist * _u;
	_vertical = 2 * halfHeight * focusDist * _v;
}

Ray Camera::getRay(float s, float t) {
	glm::vec3 rd = _lensRadius * rtrax::randomInUnitDisk();
	glm::vec3 offset = _u * rd.x + _v * rd.y;
	return Ray(_origin + offset, _lowerLeft + s * _horizontal + t * _vertical - _origin - offset);
}

