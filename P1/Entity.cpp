#include "Entity.h"

#ifdef _WIN32
	#include <gtc/matrix_transform.hpp>  
	#include <gtc/type_ptr.hpp>	
#else
	#include <glm/gtc/matrix_transform.hpp>  
	#include <glm/gtc/type_ptr.hpp>
#endif

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::upload(dmat4 const& modelViewMat) const 
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Abs_Entity()
{
  mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}
//-------------------------------------------------------------------------

void EjesRGB::update() 
{}
//-------------------------------------------------------------------------

Poligono::Poligono(dvec4 color, GLuint numL, GLdouble rd): Abs_Entity()
{
	setColor(color);
	mMesh = Mesh::generaPoligono(numL, rd);
}

Poligono::~Poligono()
{
	delete mMesh; mMesh = nullptr;
}

void Poligono::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		glColor3d(color().r, color().g, color().b);
		mMesh->render();
		glLineWidth(1);
	}
}

//-------------------------------------------------------------------------

void Poligono::update() 
{}
//-------------------------------------------------------------------------

Sierpinski::Sierpinski(dvec4 color, GLuint numP, GLdouble rd): Abs_Entity()
{
	setColor(color);
	mMesh = Mesh::generaSierpinski(rd, numP);
}

Sierpinski::~Sierpinski()
{
	delete mMesh; mMesh = nullptr;
}

void Sierpinski::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPointSize(2);
		glColor4dv(value_ptr(color()));
		mMesh->render();
		glPointSize(1);
	}
}

void Sierpinski::update() 
{}
//-------------------------------------------------------------------------

TrianguloRGB::TrianguloRGB(GLdouble rd, GLdouble radioCircunferencia): Abs_Entity()
{
	angle = 0.0;
	radio = radioCircunferencia;
	mMesh = Mesh::generaTrianguloRGB(rd);
}

TrianguloRGB::~TrianguloRGB()
{
	delete mMesh; mMesh = nullptr;
}

void TrianguloRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void TrianguloRGB::update()
{
	mModelMat = translate(dmat4(1), dvec3(radio * cos(radians(angle)), radio * sin(radians(angle)), 0.0));
	mModelMat = rotate(mModelMat, radians(angle * 100), dvec3(0.0, 0.0, 1.0));
	angle++;
}
//-------------------------------------------------------------------------

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h)
{
	mMesh = Mesh::generaRectanguloRGB(w, h);
}

RectanguloRGB::~RectanguloRGB()
{
	delete mMesh; mMesh = nullptr;
}

void RectanguloRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void RectanguloRGB::update() 
{}
//-------------------------------------------------------------------------

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h)
{
	mMesh = Mesh::generaEstrella3D(re, np, h);
}

Estrella3D::~Estrella3D()
{
	delete mMesh; mMesh = nullptr;
}

void Estrella3D::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();
		
		aMat = rotate(aMat, radians(180.0), dvec3(0.0, 1.0, 0.0));
		upload(aMat);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
void Estrella3D::update()
{

}