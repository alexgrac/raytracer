#include "material.h"


float Material::schlick(float cosine, float refIdx) {
	float r0 = (1 - refIdx) / (1 + refIdx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool Material::refract(const glm::vec3& v, const glm::vec3& n, float niOvert, glm::vec3& refracted) {
	glm::vec3 uv = glm::normalize(v);
	float dt = glm::dot(uv, n);
	float discriminant = 1.0 - niOvert * niOvert * (1 - dt * dt);

	if (discriminant > 0) {
		refracted = niOvert * (uv - n * dt) - n * std::sqrt(discriminant);
		return true;
	}

	return false;
}

glm::vec3 Material::reflect(const glm::vec3& v, const glm::vec3& n) {
	return v - 2 * glm::dot(v, n) * n;
}
