#include <iostream>
#include <fstream>
#include <glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx\norm.hpp>
#include <limits>
#include <cstdlib>

#include "sphere.h";
#include "hitablelist.h"
#include "camera.h"

#define EPSILON 0.001

using glm::vec3;

float rand01() {
	return (float(rand()) / RAND_MAX);
}

vec3 randomInUnitSphere() {
	vec3 p;
	do {
		p = float(2.0) * vec3(rand01()) - vec3(1);
	} while (glm::length2(p) >= 1.0);

	return p;
}

vec3 color(const Ray& r, IHitable *world) {
	HitRecord rec;

	if (world->hit(r, EPSILON, std::numeric_limits<float>::max(), rec)) {
		vec3 target = rec.p + rec.normal + randomInUnitSphere();
		return static_cast<float>(0.5) * color(Ray(rec.p, target - rec.p), world);
	} else {
		vec3 unit = glm::normalize(r.dir);
		float t = 0.5 * (unit.y + 1.0);
		return static_cast<float>(1.0 - t) * vec3(1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

int main() {
	size_t nx = 200;
	size_t ny = 100;
	size_t ns = 100;
	std::string filePath("image.ppm");


	// Set up the file
	std::ofstream outputStream;
	outputStream.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	outputStream.open(filePath);

	outputStream << "P3\n" << nx << " " << ny << "\n255" << std::endl;

	HitableList *world = new HitableList();
	Camera cam;

	IHitable *list1 = new Sphere(vec3(0, 0, -1), 0.5);
	world->add(list1);
	IHitable *list2 = new Sphere(vec3(0, -100.5, -1), 100);
	world->add(list2);


	for (int j = ny - 1; j >= 0; --j) {
		for (int i = 0; i < nx; ++i) {
			vec3 col(0.0);
			for (int s = 0; s < ns; ++s) {
				float u = static_cast<float>(i + (float(rand()) / RAND_MAX)) / nx;
				float v = static_cast<float>(j + (float(rand()) / RAND_MAX)) / ny;
				Ray r = cam.getRay(u, v);
				vec3 p = r.pointAtParameter(2.0);
				col += color(r, world);
			}
			col /= float(ns);
			col = vec3(sqrt(col.x), sqrt(col.y), sqrt(col.z));
			int ir = static_cast<int>(255.99 * col.r);
			int ig = static_cast<int>(255.99 * col.g);
			int ib = static_cast<int>(255.99 * col.b);

			outputStream << ir << " " << ig << " " << ib << std::endl;

		}
	}

	outputStream.close();
	delete world;

	return 0;
}