#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

class Lambertian : public Material{
	glm::vec3 _albedo;

public:

	Lambertian(const glm::vec3& albedo) : _albedo(albedo) {};

	virtual bool scatter(const Ray& r, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) override;

	~Lambertian() {};
};

#endif

