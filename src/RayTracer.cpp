// The main ray tracer.

#include <Fl/fl_ask.h>

#include "RayTracer.h"
#include "scene/light.h"
#include "scene/material.h"
#include "scene/ray.h"
#include "fileio/read.h"
#include "fileio/parse.h"
#include "ui/TraceUI.h"

// Trace a top-level ray through normalized window coordinates (x,y)
// through the projection plane, and out into the scene.  All we do is
// enter the main ray-tracing method, getting things started by plugging
// in an initial ray weight of (0.0,0.0,0.0) and an initial recursion depth of 0.
vec3f RayTracer::trace( Scene *scene, double x, double y )
{
    ray r( vec3f(0,0,0), vec3f(0,0,0) );
    scene->getCamera()->rayThrough( x,y,r );
	return traceRay( scene, r, vec3f(1.0,1.0,1.0), m_nDepth ).clamp();   // clamp(): clamps the value to go between (0,1)
}

// Do recursive ray tracing!  You'll want to insert a lot of code here
// (or places called from here) to handle reflection, refraction, etc etc.
vec3f RayTracer::traceRay( Scene *scene, const ray& r, 
	const vec3f& thresh, int depth )
{
	isect i;

	if (scene->intersect(r, i)) {

		// --------------------------------------- //
		// -------Pseudocode implementation------- //
		// --------------------------------------- //
		// Q <- ray(p,d) evaluated at t
		// I=shade()
		// R=reflectDirection()
		// I= I+material.Kr*traceRay(scene, Q, R)
		// if (ray is entering object)
		//		n_i=index_of_air
		//		n_t=material.index
		// else
		//		n_i=material.index
		//		n_t=index_of_air
		// if (notTIR())
		//		T=refractDirection()
		//		I=I+material.Kt*traceRay(scene, Q, T)
		// endif
		// return I

		double n_i;
		double n_t;

		const Material& m = i.getMaterial();
		vec3f intensity = m.shade(scene, r, i);
		intensity += m.ke;
		for (list<AmbientLight*>::const_iterator jj = scene->beginAmbientLights(); jj != scene->endAmbientLights(); jj++){
			intensity += vec3f((*jj)->getColor()[0] * m.ka[0], (*jj)->getColor()[1] * m.ka[1], (*jj)->getColor()[2] * m.ka[2]);
		}

		for (int i = 0; i < 3; i++)
			if (intensity[i]>1)
				intensity[i] = 1;

		if (depth == 0)
			return intensity;

		vec3f L = -r.getDirection();
		vec3f R = 2 * i.N.normalize() * (i.N.normalize().dot(L)) - L;
		vec3f I = traceRay(scene, ray(r.at(i.t), R), thresh, depth - 1);
		for (int i = 0; i < 3; i++)
			intensity[i] += m.kr[i] * I[i];
		/*
		if (i.N.dot(-L) < 0){
			n_i = 1.0;
			n_t = m.index;
		}
		else{
			n_i = m.index;
			n_t = 1.0;
		}
		
		if (notTIR()){
			vec3f T = refractDir();
			vec3f refractIntensity = traceRay(scene, ray(r.at(i.t), T), thresh, depth - 1);
			intensity += vec3f(m.kt[0] * refractIntensity[0], m.kt[1] * refractIntensity[1], m.kt[2] * refractIntensity[2]);
		}

		*/
		for (int i = 0; i < 3; i++)
			intensity[i] = intensity[i]>1 ? 1 : intensity[i];

		return intensity;
	
	} else {
		// can implement texture background here

		// No intersection.  This ray travels to infinity, so we color
		// it according to the background color, which in this (simple) case
		// is just black.

		return vec3f( 0.0, 0.0, 0.0 );
	}
}

RayTracer::RayTracer()
{
	buffer = NULL;
	buffer_width = buffer_height = 256;
	scene = NULL;

	m_bSceneLoaded = false;
	m_nDepth = 0;
}


RayTracer::~RayTracer()
{
	delete [] buffer;
	delete scene;
}

void RayTracer::getBuffer( unsigned char *&buf, int &w, int &h )
{
	buf = buffer;
	w = buffer_width;
	h = buffer_height;
}

double RayTracer::aspectRatio()
{
	return scene ? scene->getCamera()->getAspectRatio() : 1;
}

bool RayTracer::sceneLoaded()
{
	return m_bSceneLoaded;
}

bool RayTracer::loadScene( char* fn )
{
	try
	{
		scene = readScene( fn );
	}
	catch( ParseError pe )
	{
		fl_alert( "ParseError: %s\n", pe );
		return false;
	}

	if( !scene )
		return false;
	
	buffer_width = 256;
	buffer_height = (int)(buffer_width / scene->getCamera()->getAspectRatio() + 0.5);

	bufferSize = buffer_width * buffer_height * 3;
	buffer = new unsigned char[ bufferSize ];
	
	// separate objects into bounded and unbounded
	scene->initScene();
	
	// Add any specialized scene loading code here
	
	m_bSceneLoaded = true;

	return true;
}

void RayTracer::traceSetup( int w, int h )
{
	if( buffer_width != w || buffer_height != h )
	{
		buffer_width = w;
		buffer_height = h;

		bufferSize = buffer_width * buffer_height * 3;
		delete [] buffer;
		buffer = new unsigned char[ bufferSize ];
	}
	memset( buffer, 0, w*h*3 );
}

void RayTracer::traceLines( int start, int stop )
{
	vec3f col;
	if( !scene )
		return;

	if( stop > buffer_height )
		stop = buffer_height;

	for( int j = start; j < stop; ++j )
		for( int i = 0; i < buffer_width; ++i )
			tracePixel(i,j);
}

void RayTracer::tracePixel( int i, int j )
{
	vec3f col;

	if( !scene )
		return;

	double x = double(i)/double(buffer_width);
	double y = double(j)/double(buffer_height);

	col = trace( scene,x,y );

	unsigned char *pixel = buffer + ( i + j * buffer_width ) * 3;

	// write the rgb values into the raytracer buffer
	pixel[0] = (int)( 255.0 * col[0]);
	pixel[1] = (int)( 255.0 * col[1]);
	pixel[2] = (int)( 255.0 * col[2]);
}