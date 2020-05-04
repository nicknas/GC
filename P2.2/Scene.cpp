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
	/*for (int i = 0; i < 10; i++) {
		gTextures.push_back(new Texture());
	}
	gTextures[0]->load("../Bmps/baldosaC.bmp");
	gTextures[1]->load("../Bmps/baldosaF.bmp");
	gTextures[2]->load("../Bmps/baldosaP.bmp");
	gTextures[3]->load("../Bmps/container.bmp");
	gTextures[4]->load("../Bmps/grass.bmp", u8vec3(0,0,0), 0);
	gTextures[5]->load("../Bmps/papelC.bmp");
	gTextures[6]->load("../Bmps/papelE.bmp");
	gTextures[7]->load("../Bmps/windowC.bmp");
	gTextures[8]->load("../Bmps/windowV.bmp", 128);
	// gTextures[9]->load("../Bmps/Zelda.bmp");*/

    // Graphics objects (entities) of the scene
	/*dvec4 yellow;
	dvec4 magenta;
	magenta.r = 1.0;
	magenta.g = 0;
	magenta.b = 1.0;
	yellow.r = 1.0;
	yellow.g = 1.0;
	yellow.b = 0;*/
	gObjects.push_back(new EjesRGB(400.0));
	//PRÁCTICA 1
	/*if (mId == 0) {
		gObjects.push_back(new Poligono(yellow, 3, 300.0));
		gObjects.push_back(new Poligono(magenta, 300, 300.0));
		gObjects.push_back(new Sierpinski(yellow, 6400, 300.0));
		gObjects.push_back(new TrianguloRGB(20.0, 300.0));
		gObjects.push_back(new RectanguloRGB(800.0, 600.0));
		gObjects[5]->setModelMat(translate(gObjects[5]->modelMat(), dvec3(0.0, 0.0, -100.0)));
	}
	else if (mId == 1) {
		gObjects.push_back(new Estrella3D(50.0, 4.0, 50.0, gTextures[2], 250.0));
		gObjects.push_back(new Suelo(800.0, 600.0, 10, 10, gTextures[0]));
		gObjects.push_back(new Caja(200.0, gTextures[3], gTextures[6]));
		gObjects.push_back(new Foto(100.0, 120.0));
		gFoto = gObjects[gObjects.size() - 1];
		gObjects.push_back(new Pared(800.0, 300.0, 600.0, gTextures[8]));
		gObjects.push_back(new Planta(100.0, 5, gTextures[4]));
	}*/

	//PRÁCTICA 2.1
	/*glm::dmat4 mAux;

	Sphere* esfera = new Sphere(150.0);
	esfera->color = glm::fvec3(1, 0.5, 0);
	gObjects.push_back(esfera);
	
	Cylinder* conoDer = new Cylinder(10.0, 0, 30.0);
	conoDer->color = glm::fvec3(0, 0, 1);
	mAux = conoDer->modelMat();
	mAux = translate(mAux, dvec3(125, 50, 55));
	mAux = rotate(mAux, radians(45.0), dvec3(0.0, 1.0, 0));
	conoDer->setModelMat(mAux);
	gObjects.push_back(conoDer);
	
	Cylinder* conoIzq = new Cylinder(10.0, 0, 30.0);
	conoIzq->color = glm::fvec3(0, 1, 1);
	mAux = conoIzq->modelMat();
	mAux = translate(mAux, dvec3(75, 50, 115));
	mAux = rotate(mAux, radians(45.0), dvec3(0.0, 1.0, 0));
	conoIzq->setModelMat(mAux);
	gObjects.push_back(conoIzq);
	
	Disk* disco = new Disk(90.0,180.0);
	disco->color = glm::fvec3(1, 0, 0);
	mAux = disco->modelMat();
	mAux = translate(mAux, dvec3(0, 80, 0));
	mAux = rotate(mAux, radians(-90.0), dvec3(1.0, 0, 0));
	disco->setModelMat(mAux);
	gObjects.push_back(disco);
	
	PartialDisk* discoparcial = new PartialDisk(100.0, 120.0, 90.0,180.0);
	discoparcial->color = glm::fvec3(0, 1, 0);
	mAux = discoparcial->modelMat();
	mAux = translate(mAux, dvec3(70, 0, 70));
	mAux = rotate(mAux, radians(45.0), dvec3(0.0, 1.0, 0.0));
	//mAux = rotate(mAux, radians(15.0), dvec3(1.0, 0.0, 0.0));
	discoparcial->setModelMat(mAux);
	gObjects.push_back(discoparcial);*/

	//PRÁCTICA 2.2
	gObjects.push_back(new AnilloCuadrado());
}
//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	gObjects.clear();
	for (Texture* tx : gTextures)
	{
		delete tx; tx = nullptr;
	}
	gTextures.clear();
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.7, 0.8, 0.9, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);
}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	sceneDirLight(cam);
	cam.upload();
	
	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
}
//-------------------------------------------------------------------------

void Scene::update() const
{
	for (Abs_Entity* el : gObjects)
	{
		el->update();
	}
}
//-------------------------------------------------------------------------

void Scene::setState(int id) {
	resetGL();
	free();
	mId = id;
}

void Scene::saveFoto() {
	Texture* tex = gFoto->texture();
	tex->save("../Bmps/Foto.bmp");
}

//Práctica 2.1
void Scene::sceneDirLight(Camera const& cam) const {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
}