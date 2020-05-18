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
		glEnable(GL_COLOR_MATERIAL);
		mMesh->render();
		glDisable(GL_COLOR_MATERIAL);
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
	setModelMat(translate(mModelMat, dvec3(-mHFromOrigin, mHFromOrigin, -mHFromOrigin + 0.1)));
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
	setModelMat(translate(mModelMat, dvec3(-ld, ld / 2 + 0.1, -ld + 0.1)));
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
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
}

void Pared::update()
{

}

Planta::Planta(GLdouble ld, GLuint nump, Texture* tex)
{
	mMesh = Mesh::generaRectanguloTexCor(ld, ld, 1, 1);
	setModelMat(translate(dmat4(1), dvec3(ld*2, ld / 2, -ld*2)));
	mTexture = tex;
	numplantas = nump;
}

Planta::~Planta()
{
	delete mMesh; mMesh = nullptr;
	delete mTexture; mTexture = nullptr;
}

void Planta::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		for (int i = 0; i < numplantas; i++){
			upload(aMat);
			glDepthMask(GL_FALSE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mTexture->bind(GL_REPLACE);
			mMesh->render();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mTexture->unbind();
			glDepthMask(GL_TRUE);
			glDisable(GL_BLEND);
			aMat = rotate(aMat, radians(360.0 / numplantas), dvec3(0.0, 1.0, 0.0));
		}
	}
}

void Planta::update()
{

}

//PRÁCTICA 2.1.
QuadricEntity::QuadricEntity() {
	q = gluNewQuadric();
}

Sphere::Sphere(GLdouble rr) { 
	r = rr; 
}
void Sphere::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(this->color.x, this->color.y, this->color.z);
	// Aquí se puede fijar el modo de dibujar la esfera:
	// gluQuadricDrawStyle(q, ...);
	gluSphere(q, r, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

Cylinder::Cylinder(GLdouble base, GLdouble top, GLdouble h) {
	baseRadius = base;
	topRadius = top;
	height = h;
}
void Cylinder::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(this->color.x, this->color.y, this->color.z);
	// Aquí se puede fijar el modo de dibujar la esfera:
	// gluQuadricDrawStyle(q, ...);
	gluCylinder(q, baseRadius,topRadius, height, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

Disk::Disk(GLdouble inner, GLdouble outer) {
	innerRadius = inner;
	outerRadius = outer;
}
void Disk::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(this->color.x, this->color.y, this->color.z);
	// Aquí se puede fijar el modo de dibujar la esfera:
	// gluQuadricDrawStyle(q, ...);
	gluDisk(q, innerRadius, outerRadius, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

PartialDisk::PartialDisk(GLdouble inner, GLdouble outer, GLdouble start, GLdouble sweep) {
	innerRadius = inner;
	outerRadius = outer;
	startAngle = start;
	sweepAngle = sweep;
}
void PartialDisk::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(this->color.x, this->color.y, this->color.z);
	// Aquí se puede fijar el modo de dibujar la esfera:
	// gluQuadricDrawStyle(q, ...);
	gluPartialDisk(q, innerRadius, outerRadius, 50, 50, startAngle, sweepAngle);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

//PRÁCTICA 2.2
AnilloCuadrado::AnilloCuadrado()
{
	mMesh = Mesh::generaAnilloCuadrado();
}

AnilloCuadrado::~AnilloCuadrado()
{
	delete mMesh; mMesh = nullptr;
}

void AnilloCuadrado::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glEnable(GL_COLOR_MATERIAL);
		mMesh->render();
		glDisable(GL_COLOR_MATERIAL);	
		
	}
}

void AnilloCuadrado::update()
{}

//PRÁCTICA 2.4
EntityWithIndexMesh::EntityWithIndexMesh() {
	im = new IndexMesh();
}

void EntityWithIndexMesh::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glEnable(GL_COLOR_MATERIAL);
		mMesh->render();
		glDisable(GL_COLOR_MATERIAL);
	}
}

//------------------------------------------------------------------------
Cubo::Cubo(GLdouble arista) {
	mMesh = IndexMesh::generaIndexCuboConTapas(arista);
}
Cubo::~Cubo()
{
	delete mMesh; mMesh = nullptr;
}

void Cubo::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glEnable(GL_COLOR_MATERIAL);
		glColor3d(color().r, color().g, color().b);
		mMesh->render();
		glDisable(GL_COLOR_MATERIAL);
	}
}

void Cubo::update()
{}

//-------------------------------------------------------------------------
CompoundEntity:: ~CompoundEntity() { 
	for (Abs_Entity* el : gObjects) { 
		delete el;  el = nullptr; 
	} 
}

void CompoundEntity::render(dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
	upload(aMat);
	for (Abs_Entity* el : gObjects) {
		el->render(aMat);
	}
}

void CompoundEntity::addEntity(Abs_Entity* ae) {
	gObjects.push_back(ae);
}
//-------------------------------------------------------------------------
Cono::Cono(GLdouble h, GLdouble r, GLuint n) {
	// h=altura del cono, r=radio de la base
	// n=número de muestras, m=número de puntos del perfil
	int m = 3;
	dvec3* perfil = new dvec3[m];
	perfil[0] = dvec3(0.5, 0.0, 0.0);
	perfil[1] = dvec3(r, 0.0, 0.0);
	perfil[2] = dvec3(0.5, h, 0.0);
	
	this->mMesh = MbR::generaIndexMeshByRevolution(m, n, perfil);
}
Cono::~Cono()
{
	delete mMesh; mMesh = nullptr;
}

void Cono::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_COLOR_MATERIAL);
		glColor3d(color().r, color().g, color().b);
		mMesh->render();
		glDisable(GL_COLOR_MATERIAL);
		
	}
}

void Cono::update()
{}
//-------------------------------------------------------------------------
Esfera::Esfera(GLdouble r, GLuint p, GLuint m) {
	// r = radio de la esfera
	// p = numero de puntos (paralelo)
	// m = número de muestras (meridiano)
	dvec3* perfil = new dvec3[p];
	GLdouble angle = -90.0;
	for (int i = 0; i < p; i++) {
		perfil[i] = dvec3(r * cos(radians(angle)), r * sin(radians(angle)), 0.0);
		angle += (180.0 / (p-1));
	}
	this->mMesh = MbR::generaIndexMeshByRevolution(p, m, perfil);
}
Esfera::~Esfera()
{
	delete mMesh; mMesh = nullptr;
}

void Esfera::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glEnable(GL_COLOR_MATERIAL);
		glColor3d(color().r, color().g, color().b);
		mMesh->render();
		glDisable(GL_COLOR_MATERIAL);
	}
}

void Esfera::update()
{}