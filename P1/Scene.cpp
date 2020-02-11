#include "Scene.h"
#include "CheckML.h"

#ifdef _WIN32
	#include <gtc/matrix_transform.hpp>  
	#include <gtc/type_ptr.hpp>
#else
	#include <glm/gtc/matrix_transform.hpp>  
	#include <glm/gtc/type_ptr.hpp>
#endif

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings

	// allocate memory and load resources
    // Lights
    // Textures

    // Graphics objects (entities) of the scene
	dvec4 yellow;
	dvec4 magenta;
	magenta.r = 1.0;
	magenta.g = 0;
	magenta.b = 1.0;
	yellow.r = 1.0;
	yellow.g = 1.0;
	yellow.b = 0;
	gObjects.push_back(new EjesRGB(400.0));
	gObjects.push_back(new Poligono(yellow, 3, 300.0));
	gObjects.push_back(new Poligono(magenta, 300, 300.0));
	gObjects.push_back(new Sierpinski(yellow, 3200, 300.0));
	gObjects.push_back(new TrianguloRGB(20.0));
	gObjects.push_back(new RectanguloRGB(800.0, 600.0));
	gObjects[5]->setModelMat(translate(gObjects[5]->modelMat(), dvec3(0.0, 0.0, -100.0)));
}
//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.0, 0.0, 0.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
}
//-------------------------------------------------------------------------

void Scene::update(Camera const& cam) const
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
		el->update(cam.viewMat());
	}
}
//-------------------------------------------------------------------------
