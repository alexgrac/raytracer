#include "hitablelist.h"


bool HitableList::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
	bool hitAnything = false;
	HitRecord tempRec;
	double closestHit = t_max;

	for (auto hitable : _list) {
		if (hitable->hit(r, t_min, closestHit, tempRec)) {
			hitAnything = true;
			closestHit = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}

HitableList::~HitableList() {
	for (auto hitable : _list)
		delete hitable;
}