#include <cmath>
#include <assert.h>

#include "Box.h"

bool Box::intersectLocal( const ray& r, isect& i ) const
{
	// YOUR CODE HERE:
    // Add box intersection code here.
	// it currently ignores all boxes and just returns false.
	BoundingBox localbounds = ComputeLocalBoundingBox();
	double tMin = 1.0;
	double tMax = 1.0;
	bool booli = localbounds.intersect(r, tMin, tMax);
	if (booli == 1)
	{
		i.obj = this;
		i.t = tMin;
		if (r.at(tMin)[0] == 0.5){ i.N = vec3f(1.0, 0.0, 0.0); }
		else if (r.at(tMin)[0] == -0.5){ i.N = vec3f(-1.0, 0.0, 0.0); }
		else if (r.at(tMin)[1] == 0.5){ i.N = vec3f(0.0, 1.0, 0.0); }
		else if (r.at(tMin)[1] == -0.5){ i.N = vec3f(0.0, -1.0, 0.0); }
		else if (r.at(tMin)[2] == 0.5){ i.N = vec3f(0.0, 0.0, 1.0); }
		else if (r.at(tMin)[2] == -0.5){ i.N = vec3f(0.0, 0.0, -1.0); }
	}
	return booli;
}
