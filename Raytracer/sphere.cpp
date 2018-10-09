#include "sphere.h"

bool Sphere::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
	glm::vec3 oc = r.orig - center;
	float a = glm::dot(r.dir, r.dir);
	float b = glm::dot(oc, r.dir);
	float c = glm::dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;

	if (discriminant > 0) {
		float temp1 = (-b - sqrt(b*b - a*c)) / a;
		float temp2 = (-b + sqrt(b*b - a*c)) / a;

		if (temp1 < t_max && temp1 > t_min) {
			rec.t = temp1;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat = material;
			return true;
		}
		
		if (temp2 < t_max && temp2 > t_min) {
			rec.t = temp2;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat = material;
			return true;
		}
	}

	return false;
}
