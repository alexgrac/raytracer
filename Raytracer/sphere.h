#ifndef SPHERE_H
#define SPHERE_H

#include "ihitable.h"

class Sphere : public IHitable{
public:
	glm::vec3 center;
	float radius;
	Material *material;

	Sphere() {}
	Sphere(glm::vec3 c, float r, Material *m) : center(c), radius(r), material(m) {};

	virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
	
	~Sphere() {};
};

#endif

