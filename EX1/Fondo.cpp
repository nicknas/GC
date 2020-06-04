#include "Fondo.h"

#ifdef _WIN32
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>	
#include <gtc/matrix_access.hpp>
#else
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>
#endif

//----------------------------------------------------------------------------------------
//EXTRA 1
Fondo::Fondo() {
	malla = Mesh::generaRectanguloTexCor(800.0, 600.0, 1, 1);
	textura = new Texture();
	textura->load("../Bmps/Zelda.bmp");
	camara = new Camera(new Viewport(800, 600));
	camara->set2D();
}

Fondo::~Fondo() {
	delete malla; malla = nullptr;
	delete textura; textura = nullptr;
	delete camara; camara = nullptr;
}

void Fondo::setSize(GLsizei xw, GLsizei yh) {
	camara->setSize(xw, yh);
	camara->upload();
}

void Fondo::render() {
	if (malla != nullptr) {
		//glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		//glMatrixMode(GL_MODELVIEW);
		//glLoadMatrixd(value_ptr(camara->viewMat));
		camara->upload();
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPolygonMode(GL_FRONT, GL_FILL);
		textura->bind(GL_REPLACE);
		malla->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		textura->unbind();
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
}