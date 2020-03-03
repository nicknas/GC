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

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h, Texture *tex, GLdouble hFromOrigin)
{
	mHFromOrigin = hFromOrigin;
	mMesh = Mesh::generaEstrellaTexCor(re, np, h);
	setModelMat(translate(mModelMat, dvec3(-mHFromOrigin, mHFromOrigin, -mHFromOrigin)));
	mTexture = tex;
	angle = 0.0;
}

Estrella3D::~Estrella3D()
{
	delete mMesh; mMesh = nullptr;
	delete mTexture; mTexture = nullptr;
}

void Estrella3D::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		
		aMat = rotate(aMat, radians(180.0), dvec3(0.0, 1.0, 0.0));
		upload(aMat);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mTexture->unbind();
	}
}

void Estrella3D::update()
{
	setModelMat(translate(dmat4(1), dvec3(-mHFromOrigin, mHFromOrigin, -mHFromOrigin)));
	setModelMat(rotate(mModelMat, radians(angle), dvec3(0.0, 1.0, 0.0)));
	setModelMat(rotate(mModelMat, radians(angle), dvec3(0.0, 0.0, 1.0)));
	angle++;
}

Suelo::Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh, Texture *tex)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
	setModelMat(rotate(dmat4(1), radians(-90.0), dvec3(1.0, 0.0, 0.0)));
	mTexture = tex;
}

Suelo::~Suelo()
{
	delete mMesh; mMesh = nullptr;
	delete mTexture; mTexture = nullptr;
}

void Suelo::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mTexture->unbind();
	}
}

void Suelo::update()
{

}

Caja::Caja(GLdouble ld, Texture* frontTex, Texture* backTex) {
	mMesh = Mesh::generaCajaTexCor(ld);
	meshSuelo = Mesh::generaSueloCajaTexCor(ld);
	setModelMat(translate(mModelMat, dvec3(-ld, ld / 2 + 0.1, -ld)));
	mTexture = frontTex;
	mBackTex = backTex;
}

Caja::~Caja() {
	delete mMesh; mMesh = nullptr;
	delete meshSuelo; meshSuelo = nullptr;
	delete mTexture; mTexture = nullptr;
	delete mBackTex; mBackTex = nullptr;
}


void Caja::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glEnable(GL_CULL_FACE);
		mTexture->bind(GL_REPLACE);
		glCullFace(GL_BACK);
		mMesh->render();
		meshSuelo->render();
		mTexture->unbind();
		mBackTex->bind(GL_REPLACE);
		glCullFace(GL_FRONT);
		mMesh->render();
		meshSuelo->render();
		mBackTex->unbind();
		glDisable(GL_CULL_FACE);
	}
}

void Caja::update() 
{

}

Foto::Foto(GLdouble w, GLdouble h)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h, 1, 1);
	setModelMat(translate(dmat4(1), dvec3(0.0, 0.1, 0.0)));
	setModelMat(rotate(mModelMat, radians(-90.0), dvec3(1.0, 0.0, 0.0)));
	mTexture = new Texture();
	mTexture->loadColorBuffer();
}

Foto::~Foto()
{
	delete mMesh; mMesh = nullptr;
	delete mTexture; mTexture = nullptr;
}

void Foto::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mTexture->unbind();
	}
}

void Foto::update()
{
	mTexture->loadColorBuffer();
}

Pared::Pared(GLdouble w, GLdouble h, GLdouble s, Texture* tex)
{
	mMesh = Mesh::generaParedTexCor(w, h, s);
	setModelMat(translate(mModelMat, dvec3(0.0, h / 2, 0.0)));
	mTexture = tex;
}

Pared::~Pared()
{
	delete mMesh; mMesh = nullptr;
	delete mTexture; mTexture = nullptr;
}

void Pared::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(1, 1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mTexture->unbind();
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
}

void Pared::update()
{

}
