#include "ray.h"
#include "material.h"
#include "light.h"
#include <cmath>

// Apply the phong model to this point on the surface of the object, returning
// the color of that point.
vec3f Material::shade(Scene *scene, const ray& r, const isect& i) const
{
	// --------------------------------------- //
	// -------Pseudocode implementation------- //
	// --------------------------------------- //
	// I = I+ material.Ke+ material.Ka*scene->Ia
	// for each light source l do
	//		atten=l->distanceAttenuation()*l->shadowAttenuation()
	//		I = I + atten*(diffuseTerm + specTerm)
	// end for
	// return I

	//initiallize the parameters
	vec3f Intensity;

	//iteration in scene.lights



	for (list<Light*>::const_iterator ii = scene->beginLights(); ii != scene->endLights(); ii++)
	{
		isect is;
		// directional light or point light

		//N*L
		vec3f L = (*ii)->getDirection(r.at(i.t));
		double NdotL = i.N.dot(L);
		if (NdotL < 0.0){ NdotL = 0.0; }

		//I*Kd(N*L) (note that here I*Kd returns a vec3f type not a double type like a dot product)
		vec3f diffuse = vec3f((*ii)->getColor(r.at(i.t))[0] * kd[0],
			(*ii)->getColor(r.at(i.t))[1] * kd[1], (*ii)->getColor(r.at(i.t))[2] * kd[2]) * NdotL;

		//V*R
		vec3f V = -r.getDirection();
		vec3f R = 2 * i.N * (i.N.dot(L)) - L;
		double VdotR = V.dot(R);
		if (VdotR < 0.0){ VdotR = 0.0; }

		//I*Ks(V*R)
		vec3f specular = vec3f((*ii)->getColor(r.at(i.t))[0] * ks[0],
			(*ii)->getColor(r.at(i.t))[1] * ks[1], (*ii)->getColor(r.at(i.t))[2] * ks[2]) * pow(VdotR, shininess*128);

		//color before attenuation
		vec3f ColorBeforeAttenuation = diffuse + specular;

		//shadow attenuation
		ColorBeforeAttenuation = vec3f(ColorBeforeAttenuation[0] * (*ii)->shadowAttenuation(r.at(i.t))[0],
			ColorBeforeAttenuation[1] * (*ii)->shadowAttenuation(r.at(i.t))[1], ColorBeforeAttenuation[2] * (*ii)->shadowAttenuation(r.at(i.t))[2]);

		//distance attenuation
		double disatten = 1.0;
		if ((*ii)->distanceAttenuation(r.at(i.t)) < 1.0) {
			disatten = (*ii)->distanceAttenuation(r.at(i.t));
		}

		Intensity += ColorBeforeAttenuation * disatten;
		
	}

	return Intensity;
	//return kd;
}