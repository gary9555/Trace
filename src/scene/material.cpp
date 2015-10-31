#include "ray.h"
#include "material.h"
#include "light.h"

// Apply the phong model to this point on the surface of the object, returning
// the color of that point.
vec3f Material::shade( Scene *scene, const ray& r, const isect& i ) const
{
	// YOUR CODE HERE

	// For now, this method just returns the diffuse color of the object.
	// This gives a single matte color for every distinct surface in the
	// scene, and that's it.  Simple, but enough to get you started.
	// (It's also inconsistent with the phong model...)

	// Your mission is to fill in this method with the rest of the phong
	// shading model, including the contributions of all the light sources.
    // You will need to call both distanceAttenuation() and shadowAttenuation()
    // somewhere in your code in order to compute shadows and light falloff.

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
	vec3f SumOfDirectionalAndPoint = vec3f(0.0, 0.0, 0.0);
	int NumberOfDirectionalAndPoint = 0;

	//iteration in scene.lights

	// ambient lights
	for (list<AmbientLight*>::const_iterator jj = scene->beginAmbientLights(); jj != scene->endAmbientLights(); jj++){
		Intensity += vec3f((*jj)->getColor()[0] * ka[0], (*jj)->getColor()[1] * ka[1], (*jj)->getColor()[2] * ka[2]);
	}

	for (list<Light*>::const_iterator ii = scene->beginLights(); ii != scene->endLights(); ii++)
	{

		// directional light or point light
		NumberOfDirectionalAndPoint += 1;

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
			(*ii)->getColor(r.at(i.t))[1] * ks[1], (*ii)->getColor(r.at(i.t))[2] * ks[2]) * VdotR;

		//color before attenuation
		vec3f ColorBeforeAttenuation = diffuse + specular;

		//distance attenuation
		double disatten = 1.0;
		if ((*ii)->distanceAttenuation(r.at(i.t)) < 1.0) {
			disatten = (*ii)->distanceAttenuation(r.at(i.t));
		}

		SumOfDirectionalAndPoint += ColorBeforeAttenuation * disatten;
		Intensity += SumOfDirectionalAndPoint / NumberOfDirectionalAndPoint;
		
	}

	return Intensity;
	//return kd;
}
