#ifndef METAL_H
#define METAL_H

#include <algorithm>

#include "material.h"

class Metal : public Material{
	glm::vec3 _albedo;
	float _fuzz;

public:
	Metal(const glm::vec3& albedo, float fuzz) : _albedo(albedo) { _fuzz = std::min(fuzz, 1.0f); };

	virtual bool scatter(const Ray& r, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) override;

	~Metal() {};
};

#endif
