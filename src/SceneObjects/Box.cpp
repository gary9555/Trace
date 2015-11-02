#include <cmath>
#include <assert.h>
#include <limits>

#include "Box.h"

bool Box::intersectLocal( const ray& r, isect& i ) const
{
	BoundingBox localbounds;
	localbounds.max = vec3f(0.5, 0.5, 0.5);
	localbounds.min = vec3f(-0.5, -0.5, -0.5);

	double tMin = -1.0e308;
	double tMax = 1.0e308;
	
	if (localbounds.intersect(r, tMin, tMax))
	{

		if (tMin < RAY_EPSILON)
			return false;
		i.obj = this;
		i.t = tMin;
		if (r.at(tMin)[0] - 0.5<RAY_EPSILON && r.at(tMin)[0] - 0.5>-RAY_EPSILON){
			i.N = vec3f(1.0, 0.0, 0.0); 
		}
		else if (r.at(tMin)[0] + 0.5<RAY_EPSILON && r.at(tMin)[0] + 0.5>-RAY_EPSILON){
			i.N = vec3f(-1.0, 0.0, 0.0); 
		}
		else if (r.at(tMin)[1] - 0.5<RAY_EPSILON && r.at(tMin)[1] - 0.5>-RAY_EPSILON){
			i.N = vec3f(0.0, 1.0, 0.0); 
		}
		else if (r.at(tMin)[1] + 0.5<RAY_EPSILON && r.at(tMin)[1] + 0.5>-RAY_EPSILON){
			i.N = vec3f(0.0, -1.0, 0.0); 
		}
		else if (r.at(tMin)[2] - 0.5<RAY_EPSILON && r.at(tMin)[2] - 0.5>-RAY_EPSILON){
			i.N = vec3f(0.0, 0.0, 1.0); 
		}
		else if (r.at(tMin)[2] + 0.5<RAY_EPSILON && r.at(tMin)[2] + 0.5>-RAY_EPSILON){
			i.N = vec3f(0.0, 0.0, -1.0); 
		}
		else;

		return true;
	}
	return false;
}
