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
		explicit Estrella3D(GLdouble re, GLdouble np, GLdouble h, Texture *tex, GLdouble hFromOrigin);
		~Estrella3D();
		virtual void render(glm::dmat4 const& modelViewMat) const;
		virtual void update();
	private:
		GLdouble angle;
		GLdouble mHFromOrigin;
};

class Suelo : public Abs_Entity
{
	public:
		explicit Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh, Texture* tex);
		~Suelo();
		virtual void render(glm::dmat4 const& modelViewMat) const;
		virtual void update();
};

class Caja : public Abs_Entity
{
	public:
		explicit Caja(GLdouble ld, Texture* frontTex, Texture* backTex);
		~Caja();
		virtual void render(glm::dmat4 const& modelViewMat) const;
		virtual void update();

	private:
		Texture* mBackTex = nullptr;
		Mesh* meshSuelo = nullptr;
		glm::dmat4 matSuelo;    // modeling matrix
};

class Foto : public Abs_Entity
{
public:
	explicit Foto(GLdouble w, GLdouble h);
	~Foto();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class Pared : public Abs_Entity
{
public:
	explicit Pared(GLdouble w, GLdouble h, GLdouble s, Texture* tex);
	~Pared();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class Planta : public Abs_Entity
{
public:
	explicit Planta(GLdouble ld, GLuint nump, Texture* tex);
	~Planta();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
private:
	GLuint numplantas;

};

//PRÁCTICA 2.1
class QuadricEntity : public Abs_Entity {
public:
	QuadricEntity();
	~QuadricEntity() { gluDeleteQuadric(q); };
	glm::fvec3 color = glm::fvec3(-1, -1, -1);
protected:
	GLUquadricObj* q;
};

class Sphere : public QuadricEntity {
public:
	Sphere(GLdouble r); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble r;
};

class Cylinder : public QuadricEntity {
public:
	Cylinder(GLdouble baseRadius, GLdouble topRadius, GLdouble height); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble baseRadius, topRadius, height;
};

class Disk : public QuadricEntity {
public:
	Disk(GLdouble innerRadius, GLdouble outerRadius); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble innerRadius, outerRadius;
};

class PartialDisk : public QuadricEntity {
public:
	PartialDisk(GLdouble innerRadius, GLdouble outerRadius, GLdouble startAngle, GLdouble sweepAngle); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble innerRadius, outerRadius, startAngle, sweepAngle;
};

//PRÁCTICA 2.2
class AnilloCuadrado : public Abs_Entity {
public:
	explicit AnilloCuadrado();
	~AnilloCuadrado();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};
//PRÁCTICA 2.3 y 2.4
class EntityWithIndexMesh : public Abs_Entity {
public:
	EntityWithIndexMesh();
	~EntityWithIndexMesh() { delete im;};
	//Práctica 2.3
	virtual void render(glm::dmat4 const& modelViewMat) const;
	//virtual void update();

protected:
	IndexMesh* im;
};
//PRÁCTICA 2.4
class Cubo : public EntityWithIndexMesh {
public:
	explicit Cubo(GLdouble arista);
	~Cubo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
	//PRÁCTICA 2.6
	virtual void setCopper() const;
};
// Comentado en PRÁCTICA 2.7
/*class CompoundEntity : public Abs_Entity {
public:
	CompoundEntity() {};
	~CompoundEntity();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void addEntity(Abs_Entity* ae);
protected:
	std::vector<Abs_Entity*> gObjects;
};*/

//PRÁCTICA 2.5
class Cono : public EntityWithIndexMesh {
public:
	explicit Cono(GLdouble h, GLdouble r, GLuint n);
	~Cono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};
//PRÁCTICA 2.7
/*class Esfera : public EntityWithIndexMesh {
public:
	explicit Esfera(GLdouble r, GLuint p, GLuint m);
	~Esfera();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
	//PRÁCTICA 2.6
	virtual void setGold() const;
};*/

//-------------------------------------------------------------------------
//PRÁCTICA 2.7
class Light { // Abstract class
protected:
	static GLuint cont; // Atributo para poder generar un nuevo id cada vez
	GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS; // Primer id no válido
	// Atributos lumínicos y geométrico de la fuente de luz
	glm::fvec4 ambient = { 0.1, 0.1, 0.1, 1 };
	glm::fvec4 diffuse = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 posDir = { 0, 0, 1, 0 };
	// Añade setter’s para cambiar el valor de los atributos lumínicos

public:
	Light();
	virtual ~Light() { disable(); }
	void uploadL() const;
	// Método abstracto
	virtual void upload(glm::dmat4 const& modelViewMat) const = 0;

	void disable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glDisable(id); };
	void enable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glEnable(id); };
	void setAmb(glm::fvec4 amb) { ambient = amb; uploadL(); };
	void setDiff(glm::fvec4 diff) { diffuse = diff; uploadL(); };
	void setSpec(glm::fvec4 spec) { specular = spec; uploadL(); };
};
//-----------------------------------------------------------------------
class DirLight : public Light {
public:
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setPosDir(glm::fvec3 dir);
};
//----------------------------------------------------------
class PosLight : public Light {
protected:
	// Factores de atenuación
	GLfloat kc = 1, kl = 0, kq = 0;
public:
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setPosDir(glm::fvec3 dir);
	void setAtte(GLfloat kca, GLfloat kla, GLfloat kqa);
};
//-------------------------------------------------------------
class SpotLight : public PosLight {
protected:
	// Atributos del foco
	glm::fvec4 direction = { 0, 0, -1, 0 };
	GLfloat cutoff = 180;
	GLfloat exp = 0;
public:
	SpotLight(glm::fvec3 pos = { 0, 0, 0 })
		: PosLight() {
		posDir = glm::fvec4(pos, 1.0);
	};
	virtual void upload(glm::dmat4 const& modelViewMat)const;
	void setSpot(glm::fvec3 dir, GLfloat cf, GLfloat e);
};
//-------------------------------------------------------------------------
class Material {
protected:
	// Coeficientes de reflexión
	glm::fvec4 ambient = { 0.2, 0.2, 0.2, 1.0 };
	glm::fvec4 diffuse = { 0.8, 0.8, 0.8, 1.0 };
	glm::fvec4 specular = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat expF = 0; // Exponente para la reflexión especular
	GLuint face = GL_FRONT_AND_BACK;
	GLuint sh = GL_SMOOTH; // Tipo de matizado
public:
	Material() {};
	virtual ~Material() {};
	virtual void upload();
	void setCopper();
	void setGold();
};
//Ejercicio 33
class EntityWithMaterial : public Abs_Entity {
public:
	EntityWithMaterial() : Abs_Entity() { };
	virtual ~EntityWithMaterial() { };
	void setMaterial(Material* matl) { material = matl; };
protected:
	Material* material = nullptr;
};

class Esfera : public EntityWithMaterial {
public:
	explicit Esfera(GLdouble r, GLuint p, GLuint m);
	~Esfera();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};
//Ejercicio 34
class CompoundEntity : public Abs_Entity {
public:
	CompoundEntity();
	~CompoundEntity();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void addEntity(Abs_Entity* ae);
	SpotLight* foco;
	std::vector<Abs_Entity*> gObjects;
	
};
#endif //_H_Entities_H_