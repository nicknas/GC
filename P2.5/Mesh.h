//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#ifdef _WIN32
	#include <glm.hpp>
#else
	#include <glm/glm.hpp>
#endif

#include <vector>

//-------------------------------------------------------------------------

class Mesh 
{
public:

	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh
	static Mesh* generaPoligono(GLuint numL, GLdouble rd);
	static Mesh* generaSierpinski(GLdouble rd, GLuint numP);
	static Mesh* generaTrianguloRGB(GLdouble rd);
	static Mesh* generaRectangulo(GLdouble w, GLdouble h);
	static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h);
	static Mesh* generaEstrella3D(GLdouble re, GLdouble np, GLdouble h);
	static Mesh* generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	static Mesh* generaContCubo(GLdouble ld);
	static Mesh* generaCajaTexCor(GLdouble nl);
	static Mesh* generaSueloCajaTexCor(GLdouble nl);
	static Mesh* generaContPared(GLdouble w, GLdouble h, GLdouble s);
	static Mesh* generaParedTexCor(GLdouble w, GLdouble h, GLdouble s);
	static Mesh* generaPlanta(GLdouble w, GLdouble h, GLdouble angle);
	static Mesh* generaPlantaTexCor(GLdouble w, GLdouble h, GLdouble angle);
	//Práctica 2.2
	static Mesh* generaAnilloCuadrado();
	
	Mesh() {};
	virtual ~Mesh() {};

	Mesh(const Mesh & m) = delete;  // no copy constructor
	Mesh & operator=(const Mesh & m) = delete;  // no copy assignment
			
	virtual void render() const;
	
	GLuint size() const { return mNumVertices; };   // number of elements
	std::vector<glm::dvec3> const& vertices() const { return vVertices; };
	std::vector<glm::dvec4> const& colors() const { return vColors; };
		
protected:
	
	GLuint mPrimitive = GL_TRIANGLES;   // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0;  // number of elements ( = vVertices.size())
	std::vector<glm::dvec3> vVertices;  // vertex array
	std::vector<glm::dvec4> vColors;    // color array
	//PRÁCTICA 2.3
	std::vector<glm::dvec3> vNormals; //normal array
	virtual void draw() const;

	std::vector<glm::dvec2> vTexCoords;
};
//-------------------------------------------------------------------------
//PRÁCTICA 2.3
class IndexMesh : public Mesh {
protected:
	GLuint* vIndices = nullptr; // tabla de índices
	GLuint nNumIndices = 0;
public:
	IndexMesh() { mPrimitive = GL_TRIANGLES; }
	~IndexMesh() { delete[] vIndices; }
	virtual void render() const;
	virtual void draw() const;
	static IndexMesh* generaIndexCuboConTapas(GLdouble l);
	virtual void buildNormalVectors();
};
//-------------------------------------------------------------------------
//PRÁCTICA 2.5
class MbR : public IndexMesh {
protected:
	int m;
	int n;
	glm::dvec3* perfil;
public:
	MbR(int mm, int nn, glm::dvec3* pperfil) { m = mm; n = nn; perfil = pperfil; }
	~MbR() {}
	static MbR* generaIndexMeshByRevolution(int mm, int nn, glm::dvec3* perfil);
};
#endif //_H_Scene_H_