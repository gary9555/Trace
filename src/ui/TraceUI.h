//
// rayUI.h
//
// The header file for the UI part
//

#ifndef __rayUI_h__
#define __rayUI_h__

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Button.H>

#include <FL/fl_file_chooser.H>		// FLTK file chooser

#include "TraceGLWindow.h"

class TraceUI {
public:
	TraceUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;

	Fl_Slider*			m_sizeSlider;
	Fl_Slider*			m_depthSlider;
	Fl_Slider*			m_attenConstSlider;
	Fl_Slider*			m_attenLinearSlider;
	Fl_Slider*			m_attenQuadSlider;
	Fl_Slider*			m_ambientSlider;
	Fl_Slider*			m_intensitySlider;
	Fl_Slider*			m_distSlider;
	Fl_Slider*			m_threshSlider;


	Fl_Button*			m_renderButton;
	Fl_Button*			m_stopButton;

	TraceGLWindow*		m_traceGlWindow;

	// member functions
	void show();

	void		setRayTracer(RayTracer *tracer);

	int			getSize();
	int			getDepth();

private:
	RayTracer*	raytracer;

	int			m_nSize;
	int			m_nDepth;
	double		m_nAttenConst;
	double		m_nAttenLinear;
	double		m_nAttenQuad;
	double		m_nAmbient;
	int			m_nIntensity;
	double		m_nDist;
	vec3f		m_nThresh;

// static class members
	static Fl_Menu_Item menuitems[];

	static TraceUI* whoami(Fl_Menu_* o);

	static void cb_load_scene(Fl_Menu_* o, void* v);
	static void cb_save_image(Fl_Menu_* o, void* v);
	static void cb_exit(Fl_Menu_* o, void* v);
	static void cb_about(Fl_Menu_* o, void* v);

	static void cb_exit2(Fl_Widget* o, void* v);

	static void cb_sizeSlides(Fl_Widget* o, void* v);
	static void cb_depthSlides(Fl_Widget* o, void* v);
	static void cb_attenConstSlides(Fl_Widget* o, void* v);
	static void cb_attenLinearSlides(Fl_Widget* o, void* v);
	static void cb_attenQuadSlides(Fl_Widget* o, void* v);
	static void cb_ambientSlides(Fl_Widget* o, void* v);
	static void cb_intensitySlides(Fl_Widget* o, void* v);
	static void cb_distSlides(Fl_Widget* o, void* v);
	static void cb_threshSlides(Fl_Widget* o, void* v);

	static void cb_render(Fl_Widget* o, void* v);
	static void cb_stop(Fl_Widget* o, void* v);
};

#endif
