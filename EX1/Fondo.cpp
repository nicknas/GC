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
	malla = Mesh::generaRectanguloTexCor(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 1, 1);
	textura = new Texture();
	textura->load("../Bmps/noche.bmp");
	textura2 = new Texture(); //EXTRA 2
	textura2->load("../Bmps/Zelda.bmp",50); //EXTRA 2
	camara = new Camera(new Viewport(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)));
	camara->set2D();
}

Fondo::~Fondo() {
	delete malla; malla = nullptr;
	delete textura; textura = nullptr;
	delete textura2; textura2 = nullptr; //EXTRA 2
	delete camara; camara = nullptr;
}

void Fondo::setSizeVP(GLsizei xw, GLsizei yh) {
	camara->setViewPortSize(xw, yh);
}

void Fondo::render() {
	if (malla != nullptr) {
		
		camara->upload();
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		malla->setTwoUnits(); //EXTRA 2
		textura->bind(GL_TEXTURE0, GL_REPLACE);//EXTRA 2
		textura2->bind(GL_TEXTURE1, GL_DECAL);//EXTRA 2
		malla->render();

		textura->unbind(GL_TEXTURE0);//EXTRA 2
		textura2->unbind(GL_TEXTURE1);//EXTRA 2
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
}