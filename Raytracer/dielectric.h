#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"

class Dielectric : public Material {
	float _refIdx;

public:
	Dielectric(float refIdx) : _refIdx(refIdx) {};
	
	virtual bool scatter(const Ray& r, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) override;
	
	~Dielectric() {};
};

#endif

