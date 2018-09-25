#ifndef RAY_H
#define RAY_H

#include <glm.hpp>

class Ray {
public:
	glm::vec3 orig;
	glm::vec3 dir;

	Ray();
	Ray(glm::vec3& a, glm::vec3& b) : orig(a), dir(b) {}
	glm::vec3 pointAtParameter(float t) const { return orig + dir * t; }
	~Ray();
};

#endif

