#ifndef CSG_H
#define CSG_H

#include "../scene/scene.h"
#include "box.h"
#include "cone.h"
#include "cylinder.h"
#include "sphere.h"
#include "square.h"
#include "trimesh.h"

class csg 
	: public MaterialSceneObject
{
public:
	csg(Scene *scene, Material *mat, Box *b, Cylinder *c, double csgoerator) :MaterialSceneObject(scene, mat), bb(b), cc(c),
		operatorIndex(csgoerator){}
	virtual bool intersectLocal(const ray& r, isect& i) const;
	virtual bool hasBoundingBoxCapability() const { return true; }
	Box *bb;
	Cylinder *cc;
	int operatorIndex; //index for the operator. 0 for "union", 1 for "difference", 2 for "intersection". 
};


#endif