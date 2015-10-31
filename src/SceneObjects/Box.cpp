#include <cmath>
#include <assert.h>
#include <limits>

#include "Box.h"

bool Box::intersectLocal( const ray& r, isect& i ) const
{
	// YOUR CODE HERE:
    // Add box intersection code here.
	// it currently ignores all boxes and just returns false.
	//int a = std::numeric_limits<int>::max();
	//int b = std::numeric_limits<int>::min();
	
	//vec3f p = r.getPosition();
	//vec3f d = r.getDirection();

	//return false;

	BoundingBox localbounds;
	localbounds.max = vec3f(0.5, 0.5, 0.5);
	localbounds.min = vec3f(-0.5, -0.5, -0.5);

	double tMin;
	double tMax;
	
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
