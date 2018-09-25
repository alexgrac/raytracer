#ifndef SPHERE_H
#define SPHERE_H

#include "ihitable.h"

class Sphere : public IHitable{
public:
	glm::vec3 center;
	float radius;

	Sphere() {}
	Sphere(glm::vec3 c, float r) : center(c), radius(r) {};

	virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
	~Sphere() {};
};

#endif

