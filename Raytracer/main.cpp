#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <ctime>

#include "utils.h"
#include "sphere.h"
#include "hitablelist.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

#define EPSILON 0.001
#define MAX_DEPTH 50

using glm::vec3;


HitableList *randomScene() {
	int n = 500;
	HitableList *list = new HitableList();
	list->add(new Sphere(vec3(0, -1000, 0), 1000, new Lambertian(vec3(0.5, 0.5, 0.5))));
	int nSpheres = 11;
	for (int a = -nSpheres; a < nSpheres; a++) {
		for (int b = -nSpheres; b < nSpheres; b++) {
			float choose_mat = (float(rand()) / RAND_MAX);
			vec3 center(a + 0.9*(float(rand()) / RAND_MAX), 0.2, b + 0.9*(float(rand()) / RAND_MAX));
			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) {  // diffuse
					list->add(new Sphere(center, 0.2, new Lambertian(vec3((float(rand()) / RAND_MAX)*(float(rand()) / RAND_MAX), (float(rand()) / RAND_MAX)*(float(rand()) / RAND_MAX), (float(rand()) / RAND_MAX)*(float(rand()) / RAND_MAX)))));
				} else if (choose_mat < 0.95) { // metal
					list->add(new Sphere(center, 0.2,
						new Metal(vec3(0.5*(1 + (float(rand()) / RAND_MAX)), 0.5*(1 + (float(rand()) / RAND_MAX)), 0.5*(1 + (float(rand()) / RAND_MAX))), 0.5*(float(rand()) / RAND_MAX))));
				} else {  // glass
					list->add(new Sphere(center, 0.2, new Dielectric(1.5)));
				}
			}
		}
	}

	list->add(new Sphere(vec3(0, 1, 0), 1.0, new Dielectric(1.5)));
	list->add(new Sphere(vec3(-4, 1, 0), 1.0, new Lambertian(vec3(0.4, 0.2, 0.1))));
	list->add(new Sphere(vec3(4, 1, 0), 1.0, new Metal(vec3(0.7, 0.6, 0.5), 0.0)));

	return list;

}

vec3 color(const Ray& r, IHitable *world, int depth) {
	HitRecord rec;

	if (world->hit(r, EPSILON, std::numeric_limits<float>::max(), rec)) {
		Ray scattered;
		glm::vec3 attenuation;

		if (depth < MAX_DEPTH && rec.mat->scatter(r, rec, attenuation, scattered))
			return attenuation * color(scattered, world, depth + 1);
		else
			return vec3(0, 0, 0);
	} else {
		vec3 unit = glm::normalize(r.dir);
		float t = 0.5 * (unit.y + 1.0);
		return static_cast<float>(1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

int main() {
	int nx = 1200;
	int ny = 800;
	int ns = 100;
	std::string filePath("image.ppm");
	
	// Set up the file
	std::ofstream outputStream;
	outputStream.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	outputStream.open(filePath);

	outputStream << "P3\n" << nx << " " << ny << "\n255" << std::endl;

	HitableList *world = randomScene();
	glm::vec3 lookfrom(13, 2, 3);
	glm::vec3 lookat(0, 0, 0);
	float distToFocus = 10.0;
	float aperture = 0.1;
	Camera cam(lookfrom, lookat, glm::vec3(0,1,0), 20, float(nx)/float(ny), aperture, distToFocus);

	//HitableList *world = new HitableList();
	//IHitable *list1 = new Sphere(vec3(0, 0, -1), 0.5, new Lambertian(vec3(0.1, 0.2, 0.5)));
	//IHitable *list2 = new Sphere(vec3(0, -100.5, -1), 100, new Lambertian(vec3(0.8, 0.8, 0.0)));
	//IHitable *list3 = new Sphere(vec3(1, 0, -1), 0.5, new Metal(vec3(0.8, 0.6, 0.2), 0.3));
	//IHitable *list4 = new Sphere(vec3(-1, 0, -1), 0.5, new Dielectric(2.0));
	//IHitable *list5 = new Sphere(vec3(-1, 0, -1), -0.45, new Dielectric(2.0));
	//world->add(list1);
	//world->add(list2);
	//world->add(list3);
	//world->add(list4);
	//world->add(list5);

	//float R = cos(M_PI/4);
	//IHitable *list6 = new Sphere(glm::vec3(-R, 0, -1), R, new Lambertian(glm::vec3(0, 0, 1)));
	//IHitable *list7 = new Sphere(glm::vec3(R, 0, -1), R, new Lambertian(glm::vec3(1, 0, 0)));
	//world->add(list6);
	//world->add(list7);




	for (int j = ny - 1; j >= 0; --j) {
		for (int i = 0; i < nx; ++i) {
			vec3 col(0,0,0);
			for (int s = 0; s < ns; ++s) {
				float u = static_cast<float>(i + rtrax::rand01()) / nx;
				float v = static_cast<float>(j + rtrax::rand01()) / ny;
				Ray r = cam.getRay(u, v);
				col += color(r, world, 0);
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