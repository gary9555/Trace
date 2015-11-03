#include "csg.h"

bool csg::intersectLocal(const ray& r, isect& i) const
{
	if (operatorIndex == 0)
	{
		isect i1;
		isect i2;
		if (cc->intersectLocal(r, i1) == 1 && bb->intersectLocal(r, i2) == 0)
		{
			i = i1;
			return true;
		}

		else if (cc->intersectLocal(r, i1) == 0 && bb->intersectLocal(r, i2) == 1)
		{
			i = i2;
			return true;
		}

		else if (cc->intersectLocal(r, i1) == 0 && bb->intersectLocal(r, i2) == 0)
		{
			return false;
		}

		else if (cc->intersectLocal(r, i1) == 1 && bb->intersectLocal(r, i2) == 1)
		{
			if (i1.t < i2.t){ i = i1; }
			else { i = i2; }
			return true;
		}
	}
	else if (operatorIndex == 1)
	{
		isect i1;
		isect i2;
		if (cc->intersectLocal(r, i1) == 1 && bb->intersectLocal(r, i2) == 0)
		{
			i = i1;
			return true;
		}

		else if (cc->intersectLocal(r, i1) == 0 && bb->intersectLocal(r, i2) == 1)
		{
			return false;
		}

		else if (cc->intersectLocal(r, i1) == 0 && bb->intersectLocal(r, i2) == 0)
		{
			return false;
		}

		else if (cc->intersectLocal(r, i1) == 1 && bb->intersectLocal(r, i2) == 1)
		{
			if (i1.t < i2.t){ i = i1; }
			else {
				ray extendr = ray(r.at(i2.t + RAY_EPSILON) + 100*r.getDirection(), -r.getDirection());
				isect i3;
				if (bb->intersectLocal(extendr, i3))
				{
					i = i1;
					i.t = 100 - i3.t + i2.t;
					if (i.t > i1.t)
					{
						i.N = -i3.N;
					}
					else 
					{
						i.t = i1.t;
					}

				}
				else { i = i1; }
				i.isdifference = true;
			}
			return true;
		}
	}

	else if (operatorIndex == 2)
	{
		isect i1;
		isect i2;
		if (cc->intersectLocal(r, i1) == 1 && bb->intersectLocal(r, i2) == 0)
		{
			return false;
		}

		else if (cc->intersectLocal(r, i1) == 0 && bb->intersectLocal(r, i2) == 1)
		{
			return false;
		}

		else if (cc->intersectLocal(r, i1) == 0 && bb->intersectLocal(r, i2) == 0)
		{
			return false;
		}

		else if (cc->intersectLocal(r, i1) == 1 && bb->intersectLocal(r, i2) == 1)
		{
			if (i1.t < i2.t)
			{
				ray extendr = ray(r.at(i2.t + RAY_EPSILON) + 100 * r.getDirection(), -r.getDirection());
				isect i3;
				isect i4;
				if (bb->intersectLocal(extendr, i3) && cc->intersectLocal(extendr, i4))
				{
					if (i4.t > 100){ return false; }
					i = i2;
					i.isdifference = true;
					return true;
				}
			}
			else
			{
				ray extendr = ray(r.at(i1.t + RAY_EPSILON) + 100 * r.getDirection(), -r.getDirection());
				isect i3;
				isect i4;
				if (bb->intersectLocal(extendr, i3) && cc->intersectLocal(extendr, i4))
				{
					if (i3.t > 100){ return false; }
					i = i1;
					i.isdifference = true;
					return true;
				}
			}
			return false;
		}
	}

}