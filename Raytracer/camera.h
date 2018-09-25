#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class Camera {
	glm::vec3 _lowerLeft;
	glm::vec3 _horizontal;
	glm::vec3 _vertical;
	glm::vec3 _origin;

public:
	Camera();
	Ray getRay(float u, float v) { return Ray(_origin, _lowerLeft + u * _horizontal + v * _vertical - _origin); }
	~Camera() {};
};

#endif
