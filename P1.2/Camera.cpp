#include "Camera.h"

#ifdef _WIN32
	#include <gtc/matrix_transform.hpp>  
	#include <gtc/type_ptr.hpp>
	#include <gtc/matrix_access.hpp>
#else
	#include <glm/gtc/matrix_transform.hpp>  
	#include <glm/gtc/type_ptr.hpp>
	#include <glm/gtc/matrix_access.hpp>
#endif


using namespace glm;

//-------------------------------------------------------------------------

Camera::Camera(Viewport* vp): mViewPort(vp), mViewMat(1.0), mProjMat(1.0),  
							  xRight(vp->width() / 2.0), xLeft(-xRight),
							  yTop(vp->height() / 2.0), yBot(-yTop)
{
    setPM();
}
//-------------------------------------------------------------------------

void Camera::uploadVM() const 
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(mViewMat)); // transfers view matrix to the GPU 
}
//-------------------------------------------------------------------------

void Camera::setVM() 
{
	mViewMat = lookAt(mEye, mLook, mUp);  // glm::lookAt defines the view matrix
	setAxes();
}
//-------------------------------------------------------------------------

void Camera::set2D() 
{
	mAng = -90.0;
	mEye = dvec3(0, 0, mRadio);
	mLook = dvec3(0, 0, 0);
	mUp = dvec3(0, 1, 0);
	setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
	mAng = -45.0;

	double x = mRadio * cos(radians(mAng));
	double z = mRadio * cos(radians(mAng));

	mEye = dvec3(x, mRadio, z);  
	mLook = dvec3(0, 10, 0);   
	mUp = dvec3(0, 1, 0);
	setVM();
}
//-------------------------------------------------------------------------

/*******EJERCICIO 20
void Camera::pitch(GLdouble a) 
{  
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(1.0, 0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
}
//-------------------------------------------------------------------------

void Camera::yaw(GLdouble a) 
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 1.0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
}
//-------------------------------------------------------------------------

void Camera::roll(GLdouble a) 
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 0, 1.0));
	// glm::rotate returns mViewMat * rotationMatrix
}**/
//-------------------------------------------------------------------------

void Camera::setSize(GLdouble xw, GLdouble yh) 
{
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}
//-------------------------------------------------------------------------

void Camera::setScale(GLdouble s) 
{
	mScaleFact -= s;
	if (mScaleFact < 0) mScaleFact = 0.01;
	setPM();
}
//-------------------------------------------------------------------------
//Ejercicio 20
void Camera::setPM() 
{
	if (bOrto) { //  if orthogonal projection
		mProjMat = ortho(xLeft*mScaleFact, xRight*mScaleFact, yBot*mScaleFact, yTop*mScaleFact, mNearVal, mFarVal);
		uploadPM();
		// glm::ortho defines the orthogonal projection matrix
	}
	else {
		mProjMat = frustum(xLeft * mScaleFact, xRight * mScaleFact, yBot * mScaleFact, yTop * mScaleFact, yTop, mFarVal);
		uploadPM();
	}
}
//-------------------------------------------------------------------------

void Camera::uploadPM() const 
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(mProjMat)); // transfers projection matrix to the GPU
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------
//Ejercicio 20
void Camera::setAxes() {
	mRight = row(mViewMat, 0);
	mUpward = row(mViewMat, 1);
	mFront = -row(mViewMat, 2);
}

void Camera::moveUD(GLdouble cs) {
	mEye += mUpward * cs;
	mLook += mUpward * cs;
	setVM();
}

void Camera::moveLR(GLdouble cs) {
	mEye += mRight * cs;
	mLook += mRight * cs;
	setVM();
}

void Camera::moveFB(GLdouble cs) {
	mEye += mFront * cs;
	mLook += mFront * cs;
	setVM();
}

void Camera::orbit(GLdouble incAng, GLdouble incY) {
	mAng += incAng;
	mEye.x = mLook.x + cos(radians(mAng)) * mRadio;
	mEye.z = mLook.z - sin(radians(mAng)) * mRadio;
	mEye.y += incY;
	setVM();
}

void Camera::changePrj() {
	bOrto = !bOrto;
	setPM();
}
//Ejercicio 21
void Camera::setCenital() {
	mEye = dvec3(0, mRadio, 0);
	mLook = dvec3(0, 0, 0);
	mUp = dvec3(0, 0, -1);
	mAng = 90.0;
	setVM();
}

