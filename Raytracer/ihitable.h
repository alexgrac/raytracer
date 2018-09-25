#ifndef IHITABLE_H
#define IHITABLE_H

#include "ray.h"

struct HitRecord  {
	float t;
	glm::vec3 p;
	glm::vec3 normal;
};

class IHitable {
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};

#endif

