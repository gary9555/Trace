#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "scene.h"

enum lighttype { DIRECTIONALLIGHT, POINTLIGHT, SPOTLIGHT, AMBIENTLIGHT, NUMOFTYPES };

class Light
	: public SceneElement
{
public:
	virtual vec3f shadowAttenuation(const vec3f& P) const = 0;
	virtual double distanceAttenuation( const vec3f& P ) const = 0;
	virtual vec3f getColor( const vec3f& P ) const = 0;
	virtual vec3f getDirection( const vec3f& P ) const = 0;
	lighttype	type;


protected:
	Light( Scene *scene, const vec3f& col )
		: SceneElement( scene ), color( col ), type(DIRECTIONALLIGHT) {}

	vec3f 		color;

};

class DirectionalLight
	: public Light
{
public:
	DirectionalLight( Scene *scene, const vec3f& orien, const vec3f& color )
		: Light(scene, color), orientation(orien) {
		type = DIRECTIONALLIGHT;
	}
	virtual vec3f shadowAttenuation(const vec3f& P) const;
	virtual double distanceAttenuation( const vec3f& P ) const;
	virtual vec3f getColor( const vec3f& P ) const;
	virtual vec3f getDirection( const vec3f& P ) const;

protected:
	vec3f 		orientation;
};

class PointLight
	: public Light
{
public:
	PointLight( Scene *scene, const vec3f& pos, const vec3f& color, double constant, double linear, double quad)
		: Light(scene, color), position(pos), a(constant), b(linear), c(quad){
		type = POINTLIGHT;
	}
	virtual vec3f shadowAttenuation(const vec3f& P) const;
	virtual double distanceAttenuation( const vec3f& P ) const;
	virtual vec3f getColor( const vec3f& P ) const;
	virtual vec3f getDirection( const vec3f& P ) const;

protected:
	vec3f position;
	double a;
	double b;
	double c;
};

class SpotLight
	: public Light
{
public:
	SpotLight(Scene *scene, const vec3f& pos, const vec3f& color, double constant, double linear, double quad, vec3f boundray, vec3f direction)
		: Light(scene, color), position(pos), a(constant), b(linear), c(quad), coneboundray(boundray.normalize()), conedirection(direction.normalize()){
		type = SPOTLIGHT;
	}
	virtual vec3f shadowAttenuation(const vec3f& P) const;
	virtual double distanceAttenuation(const vec3f& P) const;
	virtual vec3f getColor(const vec3f& P) const;
	virtual vec3f getDirection(const vec3f& P) const;

protected:
	vec3f position;
	double a;
	double b;
	double c;
	vec3f coneboundray;
	vec3f conedirection;
};



class AmbientLight
	: public SceneElement{

public:
	AmbientLight(Scene *scene, const vec3f& color) :SceneElement(scene),color(color){ }
	virtual vec3f getColor() const{ return color; };

private:
	vec3f color;
	
};

#endif // __LIGHT_H__
