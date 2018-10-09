#include "dielectric.h"
#include "utils.h"


bool Dielectric::scatter(const Ray& r, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) {
	glm::vec3 outwardNormal;
	glm::vec3 reflected = reflect(r.dir, rec.normal);
	float niOverNt;
	attenuation = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 refracted;
	float cosine;
	float reflectProb;

	if (glm::dot(r.dir, rec.normal) > 0) {
		outwardNormal = -rec.normal;
		niOverNt = _refIdx;
		//cosine = glm::dot(r.dir, rec.normal) / r.dir.length();
		//cosine = glm::sqrt(1 - _refIdx * _refIdx * (1 - cosine * cosine));
		cosine = _refIdx * glm::dot(r.dir, rec.normal) / r.dir.length();
	} else {
		outwardNormal = rec.normal;
		niOverNt = 1.0 / _refIdx;
		cosine = -glm::dot(r.dir, rec.normal) / r.dir.length();
	}


	reflectProb = refract(r.dir, outwardNormal, niOverNt, refracted) ? schlick(cosine, _refIdx) : 1.0;
	
	scattered = (rtrax::rand01() < reflectProb) ? Ray(rec.p, reflected) :
		Ray(rec.p, refracted);

	return true;
}

