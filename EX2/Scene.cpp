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
	//Ejercicio 32
	setLights();

	// allocate memory and load resources
    // Lights
    // Textures
	for (int i = 0; i < 13; i++) {
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
	gTextures[9]->load("../Bmps/Zelda.bmp");
	gTextures[10]->load("../Bmps/noche.bmp");
	//gTextures[11]->load("../Bmps/checker.bmp");
	//gTextures[12]->load("../Bmps/stones.bmp");

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
	//gObjects.push_back(new AnilloCuadrado());

	//PRÁCTICA 2.3
	//gObjects.push_back(new EntityWithIndexMesh(100.0));

	//PRÁCTICA 2.4
	/*glm::dmat4 mAux;
	CompoundEntity* avion = new CompoundEntity();
	gObjects.push_back(avion);

	EntityWithIndexMesh* alas = new EntityWithIndexMesh();
	Cubo* cube = new Cubo(100.0);
	dvec4 green;
	green.r = 0.0;
	green.g = 1.0;
	green.b = 0.0;
	cube->setColor(green);
	mAux = cube->modelMat();
	mAux = scale(mAux, dvec3(4.0, 0.2, 1.75));
	cube->setModelMat(mAux);
	alas = cube;
	
	avion->addEntity(alas);
	
	CompoundEntity* chasis = new CompoundEntity();
	avion->addEntity(chasis);
	
	Sphere* bola = new Sphere(100.0);
	bola->color = glm::fvec3(1, 0, 0);
	chasis->addEntity(bola);

	CompoundEntity* helices = new CompoundEntity();
	chasis->addEntity(helices);
	
	Cylinder* cilDer = new Cylinder(20.0, 10.0, 50.0);
	cilDer->color = glm::fvec3(0, 0, 1);
	mAux = cilDer->modelMat();
	mAux = translate(mAux, dvec3(0, 0, 120));
	mAux = rotate(mAux, radians(90.0), dvec3(0.0, 1.0, 0));
	cilDer->setModelMat(mAux);
	helices->addEntity(cilDer);

	Cylinder* cilIzq = new Cylinder(20.0, 10.0, 50.0);
	cilIzq->color = glm::fvec3(0, 0, 1);
	mAux = cilIzq->modelMat();
	mAux = translate(mAux, dvec3(0, 0, 120));
	mAux = rotate(mAux, radians(-90.0), dvec3(0.0, 1.0, 0));
	cilIzq->setModelMat(mAux);
	helices->addEntity(cilIzq);*/

	//PRÁCTICA 2.5
	glm::dmat4 mAux;
	dvec4 blue;
	blue.r = 0.0;
	blue.g = 0.0;
	blue.b = 1.0;
	dvec4 clearblue;
	clearblue.r = 0.5;
	clearblue.g = 1.0;
	clearblue.b = 1.0;
	//Ejercicio 33
	Material* mat = new Material();
	mat->setGold();

	//Ejercicio 21
	//Para ver las líneas, descomentar en el render de Entity.cpp la instrucción que habilita GL_LINE
	/*Cono* cone = new Cono(200.0,100.0,30);
	cone->setColor(blue);
	gObjects.push_back(cone);*/

	//Ejercicio 22
	//Para ver las líneas, descomentar en el render de Entity.cpp la instrucción que habilita GL_LINE
	/*Esfera* esfera = new Esfera(200.0, 9, 30);
	esfera->setColor(blue);
	gObjects.push_back(esfera);*/

	//Ejercicio 23
	/*Sphere* sphere = new Sphere(100.0);
	sphere->color = glm::fvec3(0, 0, 1);
	mAux = sphere->modelMat();
	mAux = translate(mAux, dvec3(0, 0, 200));
	sphere->setModelMat(mAux);
	gObjects.push_back(sphere);

	Esfera* esfera = new Esfera(100.0, 50, 50);
	esfera->setColor(blue);
	mAux = esfera->modelMat();
	mAux = translate(mAux, dvec3(200, 0, 0));
	esfera->setModelMat(mAux);
	gObjects.push_back(esfera);*/

	//Ejercicio 24
	/*Esfera* esfera = new Esfera(180.0, 100, 100);
	esfera->setColor(clearblue);
	esfera->setMaterial(mat);
	gObjects.push_back(esfera);

	Avion* avion = new Avion();
	mAux = avion->modelMat();
	mAux = translate(mAux, dvec3(0, 250, 0));
	mAux = scale(mAux, dvec3(0.2, 0.2, 0.2));
	avion->setModelMat(mAux);
	gObjects.push_back(avion);*/
	
	/********************************************************************************************************/
	//EJERCICIOS EXTRA 2
	//ESCENA 1
	
	focoEscena1 = true;
	GridCube* gridCube = new GridCube();
	gObjects.push_back(gridCube);
	
	//ESCENA 2
	/*
	focoEscena2 = true;
	Esfera* esfera = new Esfera(180.0, 100, 100);
	esfera->setColor(clearblue);
	esfera->setMaterial(mat);
	gObjects.push_back(esfera);

	SirenCube* sirenCube = new SirenCube();
	mAux = sirenCube->modelMat();
	mAux = translate(mAux, dvec3(0, 200, 0));
	mAux = scale(mAux, dvec3(0.2, 0.2, 0.2));
	sirenCube->setModelMat(mAux);
	gObjects.push_back(sirenCube);*/
	
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
	glEnable(GL_LIGHTING); // Se activa la iluminación
	glEnable(GL_NORMALIZE); // Se activa la normalización de los vectores normales 
	
}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING); 
	glDisable(GL_NORMALIZE);
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const
{
	//Ejercicio 32
	//sceneDirLight(cam);
	//scenePosLight(cam);
	//sceneSpotLight(cam);
	
	directionalLight->upload(cam.viewMat());
	positionalLight->upload(cam.viewMat());
	spotSceneLight->upload(cam.viewMat());
	//Ejercicio 36
	minero->upload(dmat4(1.0));
	
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
	//Práctica 2.6
	//glEnable(GL_LIGHT0);
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
//PRÁCTICA 2.6
//Ejercicio 26
void Scene::scenePosLight(Camera const& cam) const {
	glEnable(GL_LIGHTING);
	
	glm::fvec4 posDir = { 300, 300, 0, 1 };
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT1, GL_POSITION, value_ptr(posDir));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 0, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT1, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT1, GL_SPECULAR, value_ptr(specular));
}
//Ejercicio 27
void Scene::sceneSpotLight(Camera const& cam) const {
	glEnable(GL_LIGHTING);
	
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0); 
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 4.0);
	glm::fvec4 posDir = { 0.0, 0.0, 300.0, 1.0 };
	glm::fvec3 direction = { 0.0,0.7,-1.0};
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT2, GL_POSITION, value_ptr(posDir));
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, value_ptr(direction));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 0, 1, 0, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT2, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT2, GL_SPECULAR, value_ptr(specular));
	
}
//Ejercicio 30
void Scene::sceneDark() const {
	//glEnable(GL_LIGHTING);
	
	glm::fvec4 ambient = { 0, 0, 0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, value_ptr(ambient));
}
//-------------------------------------------------------------------------------------
void Scene::setLights(){
	glEnable(GL_LIGHTING);

	//DirLight
	directionalLight = new DirLight();
	directionalLight->setPosDir({ 1, 1, 1 });
	directionalLight->setAmb({ 0, 0, 0, 1 });
	directionalLight->setDiff({ 1, 1, 1, 1 });
	directionalLight->setSpec({ 0.5, 0.5, 0.5, 1 });
	
	//PosLight
	positionalLight = new PosLight();
	positionalLight->setPosDir({ 300, 300, 0});
	positionalLight->setAmb({ 0, 0, 0, 1 });
	positionalLight->setDiff({ 1, 1, 0, 1 });
	positionalLight->setSpec({ 0.5, 0.5, 0.5, 1 });
	
	//SpotLight
	spotSceneLight = new SpotLight();
	spotSceneLight->setSpot({ 0.0,0.7,-1.0 }, 45.0, 4.0);
	spotSceneLight->setPosDir({ 0.0, 0.0, 300.0});
	spotSceneLight->setAmb({ 0, 0, 0, 1 });
	spotSceneLight->setDiff({ 0, 1, 0, 1 });
	spotSceneLight->setSpec({ 0.5, 0.5, 0.5, 1 });

	//Minero
	minero = new PosLight();
	minero->setPosDir({ 0, 0, 0 });
	minero->setAmb({ 0, 0, 0, 1 });
	minero->setDiff({ 1, 1, 1, 1 });
	minero->setSpec({ 0.5, 0.5, 0.5, 1 });
}
//--------------------------------------------------------------------------------------
//Ejercicio 34
void Scene::enciendeFoco(bool encencido) {
	/*Avion* avion = (Avion*)this->gObjects.at(2);
	avion->setFoco(encencido);*/

	//EJERCICIOS EXTRA 2 - ESCENA 1
	if (focoEscena1) {
		GridCube* grid = (GridCube*)this->gObjects.at(1);
		grid->setFoco(encencido);
	}
	
	//EJERCICIOS EXTRA 2 - ESCENA 2
	if (focoEscena2) {
		SirenCube* sirenCube = (SirenCube*)this->gObjects.at(2);
		sirenCube->setFoco(encencido);
	}
	

}
//--------------------------------------------------------------------------------------
//Ejercicio 35
void Scene::move() {
	GLuint time = glutGet(GLUT_ELAPSED_TIME);
	if ((time - mLUpdateTime) >= 17) {
		mLUpdateTime = time;

		glm::dmat4 mAux;
		Avion* avion = (Avion*)this->gObjects.at(2);
		CompoundEntity* chasis = avion->getChasis();
		CompoundEntity* helices = avion->getHelices();

		mAux = helices->modelMat();
		mAux = rotate(dmat4(1), radians(angle), dvec3(0.0, 0.0, 1.0));
		helices->setModelMat(mAux);

		mAux = avion->modelMat();
		mAux = translate(dmat4(1), dvec3(0.0, 250.0 * cos(radians(angle)), 250.0 * sin(radians(angle))));
		mAux = rotate(mAux, radians(angle), dvec3(1.0, 0.0, 0.0));
		mAux = scale(mAux, dvec3(0.2, 0.2, 0.2));
		avion->setModelMat(mAux);

		angle++;

		glutPostRedisplay();
	}
}
//EJERCICIOS EXTRA 2
void Scene::sirenMove() {
	GLuint time = glutGet(GLUT_ELAPSED_TIME);
	if ((time - mLUpdateTime) >= 17) {
		mLUpdateTime = time;

		glm::dmat4 mAux;
		SirenCube* sirenCube = (SirenCube*)this->gObjects.at(2);

		mAux = sirenCube->modelMat();
		mAux = translate(dmat4(1), dvec3(0.0, 200.0 * cos(radians(angle)), 200.0 * sin(radians(angle))));
		mAux = rotate(mAux, radians(angle), dvec3(1.0, 0.0, 0.0));
		mAux = scale(mAux, dvec3(0.2, 0.2, 0.2));
		sirenCube->setModelMat(mAux);
		sirenCube->updateFoco(sin(radians(angle)), cos(radians(angle)));
		angle++;

		glutPostRedisplay();
	}
}