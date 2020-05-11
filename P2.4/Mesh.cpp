#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
   
    glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
    //PRÁCTICA2.2
    //unsigned int stripIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1 };
    //glDrawElements(mPrimitive, size(), GL_UNSIGNED_INT, stripIndices);
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
    if (vTexCoords.size() > 0) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
    }
    //PRÁCTICA 2.3
    if (vNormals.size() > 0){
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_DOUBLE, 0, vNormals.data());
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    //PRÁCTICA 2.3
    glDisableClientState(GL_NORMAL_ARRAY);
    
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

Mesh* Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h)
{
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_TRIANGLE_FAN;
    mesh->mNumVertices = 2 * np + 3.0;
    mesh->vVertices.reserve(mesh->mNumVertices);
    mesh->vColors.reserve(mesh->mNumVertices);
    GLdouble angle = 90.0;
    mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
    for (int i = 1; i < (2 * np) + 3; i++) {
        if (i % 2 == 1) {
            mesh->vVertices.emplace_back(re * cos(radians(angle)), re * sin(radians(angle)), h);
        }
        else {
            mesh->vVertices.emplace_back((re / 2) * cos(radians(angle)), (re / 2) * sin(radians(angle)), h);
        }
        mesh->vColors.emplace_back(1.0, 0.0, 1.0, 1.0);
        angle += (360.0 / (2 * np));
    }
    return mesh;
}

Mesh* Mesh::generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h) {
    Mesh* mesh = generaEstrella3D(re, np, h);
    mesh->vTexCoords.reserve(mesh->mNumVertices);
    mesh->vTexCoords.emplace_back(0.5, 0.5);
    GLdouble angle = 90.0;
    for (int i = 1; i < (2 * np) + 3; i++) {
        if (i % 2 == 1) {
            mesh->vTexCoords.emplace_back(0.5 + (0.5 * cos(radians(angle))), 0.5 + (0.5 * sin(radians(angle))));
        }
        else {
            mesh->vTexCoords.emplace_back(0.5 + (0.25 * cos(radians(angle))), 0.5 + (0.25 * sin(radians(angle))));
        }
        angle += (360.0 / (2.0 * np));
    }
    return mesh;
}

Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {
    Mesh* mesh = generaRectangulo(w, h);
    mesh->vTexCoords.reserve(mesh->mNumVertices);
    mesh->vTexCoords.emplace_back(0, rh);
    mesh->vTexCoords.emplace_back(0, 0);
    mesh->vTexCoords.emplace_back(rw, rh);
    mesh->vTexCoords.emplace_back(rw, 0);
    return mesh;
}

Mesh* Mesh::generaContCubo(GLdouble ld) {
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = 10;
    mesh->vVertices.reserve(mesh->mNumVertices);
    mesh->vVertices.emplace_back(-ld/2, ld / 2, -ld / 2);
    mesh->vVertices.emplace_back(-ld / 2, -ld / 2, -ld / 2);
    mesh->vVertices.emplace_back(-ld / 2, ld / 2, ld / 2);
    mesh->vVertices.emplace_back(-ld / 2, -ld / 2, ld / 2);
    mesh->vVertices.emplace_back(ld / 2, ld / 2, ld / 2);
    mesh->vVertices.emplace_back(ld / 2, -ld / 2, ld / 2);
    mesh->vVertices.emplace_back(ld / 2, ld / 2, -ld / 2);
    mesh->vVertices.emplace_back(ld / 2, -ld / 2, -ld / 2);
    mesh->vVertices.emplace_back(-ld / 2, ld / 2, -ld / 2);
    mesh->vVertices.emplace_back(-ld / 2, -ld / 2, -ld / 2);
    return mesh;
}

Mesh* Mesh::generaCajaTexCor(GLdouble nl) {
    Mesh* mesh = generaContCubo(nl);
    mesh->vTexCoords.reserve(mesh->mNumVertices);
    mesh->vTexCoords.emplace_back(1.0, 1.0);
    mesh->vTexCoords.emplace_back(1.0, 0.0);
    mesh->vTexCoords.emplace_back(0.0, 1.0);
    mesh->vTexCoords.emplace_back(0.0, 0.0);
    mesh->vTexCoords.emplace_back(1.0, 1.0);
    mesh->vTexCoords.emplace_back(1.0, 0.0);
    mesh->vTexCoords.emplace_back(0.0, 1.0);
    mesh->vTexCoords.emplace_back(0.0, 0.0);
    mesh->vTexCoords.emplace_back(1.0, 1.0);
    mesh->vTexCoords.emplace_back(1.0, 0.0);
    return mesh;
}

Mesh* Mesh::generaSueloCajaTexCor(GLdouble nl) {
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = 4;
    
    mesh->vVertices.reserve(mesh->mNumVertices);
    mesh->vVertices.emplace_back(-nl / 2, -nl / 2, -nl / 2);
    mesh->vVertices.emplace_back(nl / 2, -nl / 2, -nl / 2);
    mesh->vVertices.emplace_back(-nl / 2, -nl / 2, nl / 2);
    mesh->vVertices.emplace_back(nl / 2, -nl / 2, nl / 2);
    
    mesh->vTexCoords.reserve(mesh->mNumVertices);
    mesh->vTexCoords.emplace_back(0.0, 1.0);
    mesh->vTexCoords.emplace_back(1.0, 1.0);
    mesh->vTexCoords.emplace_back(0.0, 0.0);
    mesh->vTexCoords.emplace_back(1.0, 0.0);
    return mesh;
}

Mesh* Mesh::generaContPared(GLdouble w, GLdouble h, GLdouble s) {
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = 10;
    mesh->vVertices.reserve(mesh->mNumVertices);
    mesh->vVertices.emplace_back(-w / 2, h / 2, -s / 2);
    mesh->vVertices.emplace_back(-w / 2, -h / 2, -s / 2);
    mesh->vVertices.emplace_back(-w / 2, h / 2, s / 2);
    mesh->vVertices.emplace_back(-w / 2, -h / 2, s / 2);
    mesh->vVertices.emplace_back(w / 2, h / 2, s / 2);
    mesh->vVertices.emplace_back(w / 2, -h / 2, s / 2);
    mesh->vVertices.emplace_back(w / 2, h / 2, -s / 2);
    mesh->vVertices.emplace_back(w / 2, -h / 2, -s / 2);
    mesh->vVertices.emplace_back(-w / 2, h / 2, -s / 2);
    mesh->vVertices.emplace_back(-w / 2, -h / 2, -s / 2);
    return mesh;
}

Mesh* Mesh::generaParedTexCor(GLdouble w, GLdouble h, GLdouble s) {
    Mesh* mesh = generaContPared(w,h,s);
    mesh->vTexCoords.reserve(mesh->mNumVertices);
    mesh->vTexCoords.emplace_back(1.0, 1.0);
    mesh->vTexCoords.emplace_back(1.0, 0.0);
    mesh->vTexCoords.emplace_back(0.0, 1.0);
    mesh->vTexCoords.emplace_back(0.0, 0.0);
    mesh->vTexCoords.emplace_back(1.0, 1.0);
    mesh->vTexCoords.emplace_back(1.0, 0.0);
    mesh->vTexCoords.emplace_back(0.0, 1.0);
    mesh->vTexCoords.emplace_back(0.0, 0.0);
    mesh->vTexCoords.emplace_back(1.0, 1.0);
    mesh->vTexCoords.emplace_back(1.0, 0.0);
    return mesh;
}

// PRÁCTICA 2.2
Mesh* Mesh::generaAnilloCuadrado(){
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = 10;
    //Vértices
    mesh->vVertices.reserve(mesh->mNumVertices);
    mesh->vVertices.emplace_back(30.0, 30.0, 0.0);
    mesh->vVertices.emplace_back(10.0, 10.0, 0.0);
    mesh->vVertices.emplace_back(70.0, 30.0, 0.0);
    mesh->vVertices.emplace_back(90.0, 10.0, 0.0);
    mesh->vVertices.emplace_back(70.0, 70.0, 0.0);
    mesh->vVertices.emplace_back(90.0, 90.0, 0.0);
    mesh->vVertices.emplace_back(30.0, 70.0, 0.0);
    mesh->vVertices.emplace_back(10.0, 90.0, 0.0);
    //mesh->vVertices.emplace_back(30.0, 30.0, 0.0);
    //mesh->vVertices.emplace_back(10.0, 10.0, 0.0);
    //Colores
    mesh->vColors.reserve(mesh->mNumVertices);
    mesh->vColors.emplace_back(0.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(1.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 1.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    //mesh->vColors.emplace_back(0.0, 0.0, 0.0, 1.0);
    //mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

    mesh->vNormals.reserve(mesh->mNumVertices);
    mesh->vNormals.emplace_back(0.0, 0.0, 1.0);
    mesh->vNormals.emplace_back(0.0, 0.0, 1.0); 
    mesh->vNormals.emplace_back(0.0, 0.0, 1.0); 
    mesh->vNormals.emplace_back(0.0, 0.0, 1.0); 
    mesh->vNormals.emplace_back(0.0, 0.0, 1.0);    
    mesh->vNormals.emplace_back(0.0, 0.0, 1.0);
    mesh->vNormals.emplace_back(0.0, 0.0, 1.0);
    mesh->vNormals.emplace_back(0.0, 0.0, 1.0);
    return mesh;
}
//PRÁCTICA 2.3

void IndexMesh::render() const
{
    if (vVertices.size() > 0) {  // transfer data
// transfer the coordinates of the vertices
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
        if (vColors.size() > 0) { // transfer colors
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
        }
        if (vTexCoords.size() > 0) {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
        }
        //PRÁCTICA 2.3
        if (vNormals.size() > 0) {
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_DOUBLE, 0, vNormals.data());
            
        }
        if (vIndices != nullptr) {
            glEnableClientState(GL_INDEX_ARRAY);
            glIndexPointer(GL_UNSIGNED_INT, 0, vIndices);
        }

        draw();

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        //PRÁCTICA 2.3
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_INDEX_ARRAY);
    }
}

// Comando para renderizar la malla indexada enviada
void IndexMesh::draw() const {
    glDrawElements(mPrimitive, nNumIndices, GL_UNSIGNED_INT, vIndices);
}

IndexMesh* IndexMesh::generaIndexCuboConTapas(GLdouble l) {
    IndexMesh* indexMesh = new IndexMesh();
    indexMesh->mPrimitive = GL_TRIANGLES;

    //Vértices
    indexMesh->mNumVertices = 8;
    indexMesh->vVertices.reserve(indexMesh->mNumVertices);
    indexMesh->vVertices.emplace_back(l / 2, l / 2, l / 2); //0
    indexMesh->vVertices.emplace_back(l / 2, -l / 2, l / 2); //1
    indexMesh->vVertices.emplace_back(l / 2, l / 2, -l / 2); //2
    indexMesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2); //3

    indexMesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2); //4 
    indexMesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2); //5
    indexMesh->vVertices.emplace_back(-l / 2, l / 2, l / 2); //6
    indexMesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2); //7
    
    //Colores
    indexMesh->vColors.reserve(indexMesh->mNumVertices);
    indexMesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    indexMesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    indexMesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    indexMesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    indexMesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    indexMesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    indexMesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    indexMesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

    //Índices
    indexMesh->nNumIndices = 36;
    GLuint indices[] = { 0, 1, 2, 2, 1, 3,
        2, 3, 4, 4, 3, 5,
        4, 5, 6, 6, 5, 7,
        6, 7, 0, 0, 7, 1,
        4, 6, 2, 2, 6, 0,
        1, 7, 3, 3, 7, 5 };
    
    indexMesh->vIndices = new GLuint[indexMesh->nNumIndices];
    for (int i = 0; i < indexMesh->nNumIndices; i++) {
        indexMesh->vIndices[i] = indices[i];
    }
    
    //Normales
    /*indexMesh->vNormals.reserve(indexMesh->mNumVertices);
    indexMesh->vNormals.emplace_back(1.0, 1.0, 2.0); //0
    indexMesh->vNormals.emplace_back(2.0, -1.0, 1.0); //1
    indexMesh->vNormals.emplace_back(2.0, 2.0, -1.0); //2
    indexMesh->vNormals.emplace_back(1.0, -2.0, -2.0); //3
    indexMesh->vNormals.emplace_back(-1.0, 1.0, -2.0); //4
    indexMesh->vNormals.emplace_back(-2.0, -1.0, -1.0); //5
    indexMesh->vNormals.emplace_back(-2.0, 2.0, 1.0); //6
    indexMesh->vNormals.emplace_back(-1.0, -2.0, 2.0); //7*/
    indexMesh->buildNormalVectors();

    return indexMesh;
 }

void IndexMesh::buildNormalVectors() {
    vNormals.reserve(mNumVertices);
    vNormals.emplace_back(0.0, 0.0, 0.0); //0
    vNormals.emplace_back(0.0, 0.0, 0.0); //1
    vNormals.emplace_back(0.0, 0.0, 0.0); //2
    vNormals.emplace_back(0.0, 0.0, 0.0); //3
    vNormals.emplace_back(0.0, 0.0, 0.0); //4
    vNormals.emplace_back(0.0, 0.0, 0.0); //5
    vNormals.emplace_back(0.0, 0.0, 0.0); //6
    vNormals.emplace_back(0.0, 0.0, 0.0); //7
    
    for (int i = 0; i < nNumIndices; i+=3) {
        int a = vIndices[i];
        int b = vIndices[i+1];
        int c = vIndices[i+2];

        dvec3 v0 = vVertices[a];
        dvec3 v1 = vVertices[b];
        dvec3 v2 = vVertices[c];
        
        dvec3 n = normalize(cross(v2-v1,v0-v1));
        
        vNormals[a] += n;
        vNormals[b] += n;
        vNormals[c] += n;
    }
    for (int i = 0; i < mNumVertices; i++) {
        vNormals[i] = normalize(vNormals[i]);
    }
}


