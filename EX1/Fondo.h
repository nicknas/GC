#pragma once
#ifndef _H_Fondo_H_
#define _H_Fondo_H_

/*EXTRA 2
#include <GL/freeglut.h>

#ifdef _WIN32
	#include <glm.hpp>
#else
	#include <glm/glm.hpp>
#endif*/
#include "GLinclude.h" //EXTRA 2

#include "Texture.h"
#include "Viewport.h"
#include "Camera.h"
#include "Mesh.h"
//-------------------------------------------------------------------------
//EXTRA 1
class Fondo {
protected:
	Mesh* malla = nullptr;
	Texture* textura = nullptr;
	Texture* textura2 = nullptr; //EXTRA 2
	Camera* camara = nullptr;
public:
	Fondo();
	~Fondo();
	void setSizeVP(GLsizei xw, GLsizei yh);
	virtual void render();
};

//-------------------------------------------------------------------------

#endif //_H_Fondo_H_