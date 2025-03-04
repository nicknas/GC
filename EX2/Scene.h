//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>

#ifdef _WIN32
	#include <glm.hpp>
#else
	#include <glm/glm.hpp>
#endif

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"

#include <vector>

class Scene	
{ 
public:
	Scene() {};
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();

    void render(Camera const& cam) const;
	void update() const;
	void setState(int id);
	void saveFoto();
	//Pr�ctica 2.1
	void sceneDirLight(Camera const& cam) const;
	//PR�CTICA 2.6
	void scenePosLight(Camera const& cam) const;
	void sceneSpotLight(Camera const& cam) const;
	void sceneDark() const;
	//PR�CTICA 2.7
	void setLights();
	//Ejercicio 34
	void enciendeFoco(bool encencido);
	//Ejercicio 35
	void move();
	//EJERCICIOS EXTRA 2
	void sirenMove();

	DirLight* directionalLight;
	PosLight* positionalLight;
	SpotLight* spotSceneLight;
	//Ejericio 36
	PosLight* minero;
protected:
	void free();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures;
	Abs_Entity* gFoto;
	int mId = 0;

	//Ejercicio 35
	GLuint mLUpdateTime = 0;
	GLdouble angle = 0.0;

	//EJERCICIOS EXTRA 2
	bool focoEscena1 = false;
	bool focoEscena2 = false;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

