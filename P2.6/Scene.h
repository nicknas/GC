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

//-------------------------------------------------------------------------

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
	//Práctica 2.1
	void sceneDirLight(Camera const& cam) const;
	//PRÁCTICA 2.6
	void scenePosLight(Camera const& cam) const;
	void sceneSpotLight(Camera const& cam) const;

	bool activateDirLight = true;
	bool activatePosLight = false;
	bool activateSpotLight = false;
	bool ilumSpot = false;
protected:
	void free();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures;
	Abs_Entity* gFoto;
	int mId = 0;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

