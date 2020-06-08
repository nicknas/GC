#include "IG1App.h"
#include "CheckML.h"
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// static single instance (singleton pattern)

IG1App IG1App::s_ig1app;  // default constructor (constructor with no parameters)

//-------------------------------------------------------------------------

void IG1App::close()  
{
	if (!mStop) {  // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
		mStop = true;   // main loop stopped  
	}
	free();
}
//-------------------------------------------------------------------------

void IG1App::run()   // enters the main event processing loop
{
	if (mWinId == 0) { // if not initialized
		init();       // initialize the application 
		glutMainLoop();      // enters the main event processing loop 
		mStop = true;  // main loop has stopped  
	}
}
//-------------------------------------------------------------------------

void IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();   
	

	// create the scene after creating the context 
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera = new Camera(mViewPort);
	mScene = new Scene;
	
	mFondo = new Fondo(mViewPort); //EXTRA 1
	mCamera->set2D();
	
	
	//mFondo->setSize(mWinW, mWinH);
	mScene->init();
	
}
//-------------------------------------------------------------------------

void IG1App::iniWinOpenGL() 
{  // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);
		
	glutInitContextVersion(3, 0);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);		// GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(mWinW, mWinH);   // window size
	//glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer   
	
	mWinId = glutCreateWindow("IG1App");  // with its associated OpenGL context, return window's identifier 
	
	if (!gladLoadGL()) { printf("GLAD: Something went wrong!\n"); } // EXTRA 2

	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);
	glutIdleFunc(s_update);
	//Ejercicio 20
	glutMouseFunc(s_mouse); // cuando se presiona o suelta un botón
	glutMotionFunc(s_motion); // cuando se mueve con un botón presionado
	glutMouseWheelFunc(s_mouseWheel); // cuando se gira una rueda

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}
//-------------------------------------------------------------------------

void IG1App::free() 
{  // release memory and resources
	delete mScene; mScene = nullptr;
	delete mCamera; mCamera = nullptr;
	delete mViewPort; mViewPort = nullptr;
	//EXTRA 1
	delete mFondo; mFondo = nullptr;
}
//-------------------------------------------------------------------------
//Ejercicio 21
void IG1App::display()   
{  // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clears the back buffer

	
	mFondo->render();//EXTRA 1
	if (m2Vistas) display2Vistas();
	else 
		mScene->render(*mCamera);  // uploads the viewport and camera to the GPU
	
	glutSwapBuffers();	// swaps the front and back buffer
}
//-------------------------------------------------------------------------

void IG1App::resize(int newWidth, int newHeight) 
{
	mWinW = newWidth; mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height()); 

	
	mFondo->setSize(mViewPort->width(), mViewPort->height());//EXTRA 1
}
//-------------------------------------------------------------------------

void IG1App::key(unsigned char key, int x, int y) 
{
	bool need_redisplay = true;
	
	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
	case '+':
		mCamera->setScale(+0.01);  // zoom in  (increases the scale)
		break;
	case '-':
		mCamera->setScale(-0.01);  // zoom out (decreases the scale)
		break;
	case 'l':
		mCamera->set3D();
		break;
	case 'o':
		mCamera->set2D();
		break;
	case 'u':
		mAnimate = !mAnimate;
		break;
	case '1':
		mScene->setState(1);
		mScene->init();
		break;
	case '0':
		mScene->setState(0);
		mScene->init();
		break;
	case 'v':
		mScene->saveFoto();
		break;
	//Ejercicio 20
	case 'p':
		mCamera->changePrj();
		break;
	case 'k':
		m2Vistas = !m2Vistas;
		break;
	//PRÁCTICA 2.6
	//Ejercicio 25
	case 'q':
		//Ejercicio 32
		//glEnable(GL_LIGHT0);
		mScene->directionalLight->enable();
		break;
	case 'w':
		//Ejercicio 32
		//glDisable(GL_LIGHT0);
		mScene->directionalLight->disable();
		break;
	//Ejercicio 26
	case 'a':
		//Ejercicio 32
		//glEnable(GL_LIGHT1);
		mScene->positionalLight->enable();
		break;
	case 's':
		//Ejercicio 32
		//glDisable(GL_LIGHT1);
		mScene->positionalLight->disable();
		break;
	//Ejercicio 27
	case 'z':
		//Ejercicio 32
		//glEnable(GL_LIGHT2);
		mScene->spotSceneLight->enable();
		break;
	case 'x':
		//Ejercicio 32
		//glDisable(GL_LIGHT2);
		mScene->spotSceneLight->disable();
		break;
	//Ejercicio 30
	case 'e':
		mScene->sceneDark();
		break;
	//Ejercicio 34
	case 't':
		mScene->enciendeFoco(true);
		break;
	case 'g':
		mScene->enciendeFoco(false);
		break;
	//Ejercicio 35
	case 'y':
		mScene->move();
		break;
	//Ejercicio 34
	case 'd':
		mScene->minero->enable();
		break;
	case 'f':
		mScene->minero->disable();
		break;
	default:
		need_redisplay = false;
		break;
	} //switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

void IG1App::specialKey(int key, int x, int y) 
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)
	
	switch (key) {
	case GLUT_KEY_RIGHT:
		if (mdf == GLUT_ACTIVE_CTRL)
			//mCamera->pitch(-1);   // rotates -1 on the X axis
			mCamera->moveLR(-1);
		else
			//mCamera->pitch(1);    // rotates 1 on the X axis
			mCamera->moveLR(1);
		break;
	case GLUT_KEY_LEFT:
		if (mdf == GLUT_ACTIVE_CTRL)
		    //mCamera->yaw(1);      // rotates 1 on the Y axis
			mCamera->moveUD(1);
		else 
			//mCamera->yaw(-1);     // rotate -1 on the Y axis 
			mCamera->moveUD(-1);
		break;
	case GLUT_KEY_UP:
		//mCamera->roll(1);    // rotates 1 on the Z axis
		mCamera->moveFB(1);
		break;
	case GLUT_KEY_DOWN:
		//mCamera->roll(-1);   // rotates -1 on the Z axis
		mCamera->moveFB(-1);
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

void IG1App::update() {
	if (mAnimate) {
		GLuint time = glutGet(GLUT_ELAPSED_TIME);
		if ((time - mLastUpdateTime) >= 17) {
			mLastUpdateTime = time;
			mScene->update();
			glutPostRedisplay();
		}
	}
}

int IG1App::winWidth() {
	return mWinW;
}
int IG1App::winHeight() {
	return mWinH;
}

//Ejercicio 20
//--------------------------------------------------------------
void IG1App::mouse(int button, int state, int x, int y) {
	mMouseButt = button;
	mMouseCoord = glm::dvec2(x, mWinH - y);
}
//-----------------------------------------------------------------

void IG1App::motion(int x, int y) {
	if (mMouseButt == GLUT_LEFT_BUTTON) {
		// guardamos la anterior posición en var. temp.
		glm::dvec2 mp = mMouseCoord;
		// Guardamos la posición actual
		mMouseCoord = glm::dvec2(x, mWinH - y);
		mp = (mMouseCoord - mp); // calculamos el desplazamiento realizado
		mCamera->orbit(-mp.x * 0.05, -mp.y); // sensitivity = 0.05
		glutPostRedisplay();
	}
	else if (mMouseButt == GLUT_RIGHT_BUTTON) {
		// guardamos la anterior posición en var. temp.
		glm::dvec2 mp = mMouseCoord;
		// Guardamos la posición actual
		mMouseCoord = glm::dvec2(x, mWinH - y);
		mp = (mMouseCoord - mp); // calculamos el desplazamiento realizado
		//mCamera->orbit(mp.x, mp.y * 0.05); // sensitivity = 0.05
		mCamera->moveLR(-mp.x);
		mCamera->moveUD(-mp.y);
		glutPostRedisplay();
	}
}
//-----------------------------------------------------------------

void IG1App::mouseWheel(int whellNumber, int direction, int x, int y) {
	int m = glutGetModifiers();
	if (m == 0) {
		// direction es la dirección de la rueda (+1 / -1)
		if (direction == 1) mCamera->moveFB(5.0);
		else mCamera->moveFB(-5.0);
	}
	else if (m == GLUT_ACTIVE_CTRL) {
		if (direction == 1) mCamera->setScale(+0.01);
		else mCamera->setScale(-0.01);
	}
	
	glutPostRedisplay();
}

//-----------------------------------------------------------------------
//Ejercicio 21
void IG1App::display2Vistas() {
	Camera auxCam = *mCamera; //Camara auxiliar
	Viewport auxVP = *mViewPort; //Puerto de vista auxiliar
	mViewPort->setSize(mWinW / 2, mWinH); //Tamaño de los 2 puertos de vista
	auxCam.setSize(mViewPort->width(), mViewPort->height());//tamaño de la venta de vista de la cámara
	// vista Usuario
	mViewPort->setPos(0, 0); //Posición del puerto de vista
	mScene->render(auxCam); //renderizar con puerto de vista y cámara configurados
	// vista Cenital
	mViewPort->setPos(mWinW / 2, 0);//Posición del puerto de vista
	auxCam.setCenital(); //Cambiamos posición y orientación de la cámara
	mScene->render(auxCam); //renderizar con puerto de vista y cámara configurados
	*mViewPort = auxVP; // restaurar el puerto de vista
}