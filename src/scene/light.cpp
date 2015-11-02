#include <cmath>
#include <iostream>
#include "light.h"

double DirectionalLight::distanceAttenuation( const vec3f& P ) const
{
	// distance to light is infinite, so f(di) goes to 0.  Return 1.
	return 1.0;
}


vec3f DirectionalLight::shadowAttenuation( const vec3f& P ) const
{
    // YOUR CODE HERE:
    // You should implement shadow-handling code here.
	isect i;
	if (scene->intersect(ray(P, getDirection(P)), i)){ return vec3f(0.0, 0.0, 0.0); }

    return vec3f(1,1,1);
}

vec3f DirectionalLight::getColor( const vec3f& P ) const
{
	// Color doesn't depend on P 
	return color;
}

vec3f DirectionalLight::getDirection( const vec3f& P ) const
{
	return -orientation;
}

double PointLight::distanceAttenuation( const vec3f& P ) const
{
	double dist = (position - P).length();
	double distatten = 1 / (a + b*dist + c*dist*dist);

	return distatten>1 ? 1:distatten;
}

double SpotLight::distanceAttenuation(const vec3f& P) const
{
	double dist = (position - P).length();
	double distatten = 1 / (a + b*dist + c*dist*dist);

	return distatten>1 ? 1 : distatten;
}


vec3f PointLight::getColor( const vec3f& P ) const
{
	// Color doesn't depend on P 
	return color;
}

vec3f SpotLight::getColor(const vec3f& P) const
{
	// Color doesn't depend on P 
	return color;
}

vec3f PointLight::getDirection( const vec3f& P ) const
{
	return (position - P).normalize();
}

vec3f SpotLight::getDirection(const vec3f& P) const
{
	return (position - P).normalize();
}


vec3f PointLight::shadowAttenuation(const vec3f& P) const
{
    // You should implement shadow-handling code here.
	isect i;
	if (scene->intersect(ray(P, getDirection(P)), i)){ return vec3f(0.0, 0.0, 0.0); }
    return vec3f(1,1,1);
}

vec3f SpotLight::shadowAttenuation(const vec3f& P) const
{
	isect i;
	if (coneboundray*conedirection > -getDirection(P)*conedirection){ return vec3f(0.0, 0.0, 0.0); }
	if (scene->intersect(ray(P, getDirection(P)), i)){ return vec3f(0.0, 0.0, 0.0); }
	return vec3f(1, 1, 1);
}

