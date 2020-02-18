//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>

#ifdef _WIN32
	#include <glm.hpp>
#else
	#include <glm/glm.hpp>
#endif

#include "Mesh.h"
#include "Texture.h"
//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity() : mModelMat(1.0), mColor(1) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method
	virtual void update() {};

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	void setColor(glm::dvec4 const& color) { mColor = color; };
	glm::dvec4 const& color() const { return mColor; };

	void setTexture(Texture *aTex) { mTexture = aTex; };
	Texture* texture() const { return mTexture; };
	
protected:

	Mesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix
	glm::dvec4 mColor;
	Texture* mTexture = nullptr;
	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
	public:
		explicit EjesRGB(GLdouble l);
		~EjesRGB();
		virtual void render(glm::dmat4 const& modelViewMat) const;
		virtual void update();
};

//-------------------------------------------------------------------------

class Poligono : public Abs_Entity
{
	public:
		explicit Poligono(glm::dvec4 color, GLuint numL, GLdouble rd);
		~Poligono();
		virtual void render(glm::dmat4 const& modelViewMat) const;
		virtual void update();
};

class Sierpinski : public Abs_Entity
{
	public:
		explicit Sierpinski(glm::dvec4 color, GLuint numP, GLdouble rd);
		~Sierpinski();
		virtual void render(glm::dmat4 const& modelViewMat) const;
		virtual void update();
};

class TrianguloRGB : public Abs_Entity
{
	public:
		explicit TrianguloRGB(GLdouble rd, GLdouble radioCircunferencia);
		~TrianguloRGB();
		virtual void render(glm::dmat4 const& modelViewMat) const;
		virtual void update();
	private:
		GLdouble angle;
		GLdouble radio;
};

class RectanguloRGB : public Abs_Entity
{
	public:
		explicit RectanguloRGB(GLdouble w, GLdouble h);
		~RectanguloRGB();
		virtual void render(glm::dmat4 const& modelViewMat) const;
		virtual void update();
};

class Estrella3D : public Abs_Entity
{
	public:
		explicit Estrella3D(GLdouble re, GLdouble np, GLdouble h);
		~Estrella3D();
		virtual void render(glm::dmat4 const& modelViewMat) const;
		virtual void update();
	private:
		GLdouble angle;
};
#endif //_H_Entities_H_