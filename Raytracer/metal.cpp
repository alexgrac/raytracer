#include "metal.h"
#include "utils.h"

bool Metal::scatter(const Ray& r, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) {
	glm::vec3 reflected = reflect(glm::normalize(r.dir), rec.normal);
	scattered = Ray(rec.p, reflected + _fuzz * rtrax::randomInUnitSphere());
	attenuation = _albedo;

	return glm::dot(scattered.dir, rec.normal) > 0;
}