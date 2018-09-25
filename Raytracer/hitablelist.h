#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include <vector>
#include "ihitable.h"

class HitableList : public IHitable{
	std::vector<IHitable*> _list;

public:
	HitableList() {};
	HitableList(std::vector<IHitable*>& l) : _list(l) {};
	virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
	void add(IHitable* hitable) { _list.push_back(hitable); }
	~HitableList();
};

#endif

