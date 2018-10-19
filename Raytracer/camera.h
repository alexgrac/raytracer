#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class Camera {
	glm::vec3 _lowerLeft;
	glm::vec3 _horizontal;
	glm::vec3 _vertical;
	glm::vec3 _origin;
	glm::vec3 _u, _v, _w;
	float _lensRadius;

public:
	Camera(glm::vec3 lookFrom, glm::vec3 lookAt, glm::vec3 up, float vfov, float aspect, float aperture, float focusDist);
	Ray getRay(float s, float t);
	~Camera() {};
};

#endif
