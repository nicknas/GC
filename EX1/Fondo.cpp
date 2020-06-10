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
Fondo::Fondo(Viewport* vp) {
	malla = Mesh::generaRectanguloTexCor(vp->width(), vp->height(), 1, 1);
	textura = new Texture();
	textura->load("../Bmps/noche.bmp");
	textura2 = new Texture();
	textura2->load("../Bmps/Zelda.bmp",50);
	camara = new Camera(vp);
	camara->set2D();
}

Fondo::~Fondo() {
	delete malla; malla = nullptr;
	delete textura; textura = nullptr;
	delete textura2; textura2 = nullptr;
	delete camara; camara = nullptr;
}

void Fondo::setSize(GLsizei xw, GLsizei yh) {
	camara->setSize(xw, yh);
	malla = Mesh::generaRectanguloTexCor(xw, yh, 1, 1);
}

void Fondo::render() {
	if (malla != nullptr) {
		
		camara->upload();
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glPolygonMode(GL_FRONT, GL_FILL);
		
		malla->setTwoUnits();
		textura->bind(GL_TEXTURE0, GL_REPLACE);//EXTRA 2
		textura2->bind(GL_TEXTURE1, GL_DECAL);//EXTRA 2
		malla->render();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		textura->unbind(GL_TEXTURE0);//EXTRA 2
		textura2->unbind(GL_TEXTURE0);//EXTRA 2
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
}