//#pragma once
#ifndef _H_Camera_H_
#define _H_Camera_H_

/*EXTRA 2
#include <GL/freeglut.h>

#ifdef _WIN32
	#include <glm.hpp>
#else
	#include <glm/glm.hpp>
#endif*/
#include "GLinclude.h" //EXTRA 2

#include "Viewport.h"

//-------------------------------------------------------------------------

class Camera {
public:
	explicit Camera(Viewport* vp);
	~Camera() {};

	// viewPort
	Viewport const& viewPort() const { return *mViewPort; };

	// view matrix 
	glm::dmat4 const& viewMat() const { return mViewMat; };
	
	void set2D();
	void set3D();
	
	/******Ejercicio 20
	void pitch(GLdouble a); // rotates a degrees on the X axis
	void yaw(GLdouble a);   // rotates a degrees on the Y axis
	void roll(GLdouble a);  // rotates a degrees on the Z axis
	*/
	// projection matrix
	glm::dmat4 const& projMat() const { return mProjMat; };
	
	// sets scene visible area size 
	void setSize(GLdouble xw, GLdouble yh);
	// updates the scale factor 
	void setScale(GLdouble s);

	// transfers its viewport, the view matrix and projection matrix to the GPU
	void upload() const { mViewPort->upload();  uploadVM(); uploadPM(); }; 

	//Ejercicio 20
	void moveUD(GLdouble cs);
	void moveLR(GLdouble cs);
	void moveFB(GLdouble cs);
	void orbit(GLdouble incAng, GLdouble incY);
	void changePrj();
	//Ejercicio 21
	void setCenital();

protected:
	
	glm::dvec3 mEye = { 0.0, 0.0, 500.0 };  // camera's position
	glm::dvec3 mLook = { 0.0, 0.0, 0.0 };   // target's position
	glm::dvec3 mUp = { 0.0, 1.0, 0.0 };     // the up vector 

	glm::dmat4 mViewMat;    // view matrix = inverse of modeling matrix 
	void setVM();
	void uploadVM() const;  // transfers viewMat to the GPU

	glm::dmat4 mProjMat;     // projection matrix
	void setPM();
	void uploadPM() const;   // transfers projMat to the GPU

	GLdouble xRight, xLeft, yTop, yBot;      // size of scene visible area
	GLdouble mNearVal = 1, mFarVal = 10000;  // view volume
	GLdouble mScaleFact = 1;   // scale factor
	bool bOrto = true;   // orthogonal or perspective projection

	Viewport* mViewPort;   // the viewport

	//Ejercicio 20
	glm::dvec3 mRight, mUpward, mFront;
	void setAxes();
	GLdouble mAng = 90.0, mRadio=1000.0;
};
//-------------------------------------------------------------------------

#endif //_H_Camera_H_