#pragma once
#include <Windows.h>
// una de las siguientes dos líneas según la organización del proyecto
#include "glad.h" //OpenGL Loader Generator //EXTRA 2
#include <GL/freeglut.h> // OpenGL Utility Toolkit
#ifdef _WIN32
#include <glm.hpp>
#else
#include <glm/glm.hpp>
#endif