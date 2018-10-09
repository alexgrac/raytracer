#ifndef MATERIAL_H
#define MATERIAL_H

#include "ihitable.h"

class Material {

public:
	glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n);
	bool refract(const glm::vec3& v, const glm::vec3& n, float niOvert, glm::vec3& refracted);
	float schlick(float cosine, float refIdx);

	virtual bool scatter(const Ray& r, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) = 0;
	
};

#endif
