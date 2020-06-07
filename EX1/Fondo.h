#pragma once
#ifndef _H_Fondo_H_
#define _H_Fondo_H_

#include <GL/freeglut.h>

#ifdef _WIN32
#include <glm.hpp>
#else
#include <glm/glm.hpp>
#endif

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
	Camera* camara = nullptr;
public:
	Fondo(Viewport* vp);
	~Fondo();
	void setSize(GLsizei xw, GLsizei yh);
	virtual void render();
};

//-------------------------------------------------------------------------

#endif //_H_Fondo_H_