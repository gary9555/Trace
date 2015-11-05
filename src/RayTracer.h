#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__

// The main ray tracer.

#include "scene/scene.h"
#include "scene/ray.h"

class RayTracer
{
public:
    RayTracer();
    ~RayTracer();

    vec3f	trace( Scene *scene, double x, double y, vec3f thresh );
	vec3f	traceRay( Scene *scene, const ray& r, const vec3f& thresh, int depth );


	void	getBuffer( unsigned char *&buf, int &w, int &h );
	double	aspectRatio();
	void	traceSetup( int w, int h );
	void	traceLines( int start = 0, int stop = 10000000 );
	void	tracePixel( int i, int j, vec3f thresh );

	bool	loadScene( char* fn );

	bool	sceneLoaded();

	void	setDepth(int depth){ m_nDepth = depth; }

private:
	unsigned char *buffer;
	int		buffer_width, buffer_height;
	int		bufferSize;
	Scene	*scene;

	bool	m_bSceneLoaded;
	int		m_nDepth;
	vec3f	mythresh = vec3f(0.0, 0.0, 0.0);
};

#endif // __RAYTRACER_H__
