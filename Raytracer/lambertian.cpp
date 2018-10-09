#include "lambertian.h"
#include "utils.h"


bool Lambertian::scatter(const Ray& r, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) {
	glm::vec3 target = rec.p + rec.normal + rtrax::randomInUnitSphere();
	scattered = Ray(rec.p, target - rec.p);
	attenuation = _albedo;

	return true;
}

