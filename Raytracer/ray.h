#ifndef RAY_H
#define RAY_H

#include <glm.hpp>

class Ray {
public:
	glm::vec3 orig;
	glm::vec3 dir;

	Ray();
	Ray& operator=(const Ray& other) { orig = other.orig; dir = other.dir; return *this; }
	Ray(const glm::vec3& a, const glm::vec3& b) : orig(a), dir(b) {}
	glm::vec3 pointAtParameter(float t) const { return orig + dir * t; }
	~Ray();
};

#endif

