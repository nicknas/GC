#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}
//-------------------------------------------------------------------------
Mesh* Mesh::generaPoligono(GLuint numL, GLdouble rd)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_LINE_LOOP;

    mesh->mNumVertices = numL;
    mesh->vVertices.reserve(mesh->mNumVertices);

    GLdouble angle = 90.0;
    for (int i = 0; i < numL; i++) {
        mesh->vVertices.emplace_back(rd * cos(radians(angle)), rd * sin(radians(angle)), 0.0);
        angle += (360.0 / numL);
    }
    return mesh;
}

Mesh* Mesh::generaSierpinski(GLdouble rd, GLuint numP) 
{
    Mesh* triangulo = generaPoligono(3, rd);
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_POINTS;
    mesh->mNumVertices = numP;
    mesh->vVertices.reserve(mesh->mNumVertices);
    mesh->vVertices.emplace_back(triangulo->vVertices[rand() % 3]);
    for (GLuint k = 1; k < numP; k++) {
        dvec3 randomVertice = triangulo->vVertices[rand() % 3];
        dvec3 newPoint = dvec3((randomVertice.x + mesh->vVertices[k-1].x) / 2, (randomVertice.y + mesh->vVertices[k-1].y) / 2, (randomVertice.z + mesh->vVertices[k-1].z) / 2 );
        mesh->vVertices.emplace_back(newPoint);
    }
    delete triangulo;
    triangulo = nullptr;
    return mesh;
}

Mesh* Mesh::generaTrianguloRGB(GLdouble rd) 
{
    Mesh* mesh = generaPoligono(3, rd);
    mesh->mPrimitive = GL_TRIANGLES;
    mesh->vColors.reserve(mesh->mNumVertices);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    return mesh;
}

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h) 
{
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(-(w / 2), h / 2, 0.0);
    mesh->vVertices.emplace_back(-(w / 2), -(h / 2), 0.0);
    mesh->vVertices.emplace_back(w / 2, h / 2, 0.0);
    mesh->vVertices.emplace_back(w / 2, -(h / 2), 0.0);
    return mesh;
}

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h)
{
    Mesh* mesh = generaRectangulo(w, h);
    mesh->vColors.reserve(mesh->mNumVertices);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(0.5, 0.5, 0.5, 1.0);
    return mesh;
}
