#include <cmath>
#include <assert.h>
#include <limits>

#include "Box.h"

bool Box::intersectLocal( const ray& r, isect& i ) const
{
	// YOUR CODE HERE:
    // Add box intersection code here.
	// it currently ignores all boxes and just returns false.
	int a = std::numeric_limits<int>::max();
	int b = std::numeric_limits<int>::min();
	
	vec3f p = r.getPosition();
	vec3f d = r.getDirection();

	return false;
}
