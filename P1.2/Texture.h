//#pragma once
#ifndef _H_Texture_H_
#define _H_Texture_H_

#include <GL/freeglut.h>
#ifdef _WIN32
  #include <glm.hpp>
#else
  #include <glm/glm.hpp>
#endif
#include "Pixmap32RGBA.h"
#include <string>

//-------------------------------------------------------------------------

class Texture
{
public:
  Texture(){};
  ~Texture();

  Texture(const Texture & tex) = delete;  // no copy constructor
  Texture & operator=(const Texture & tex) = delete;  // no copy assignment

  void load(const std::string & BMP_Name, GLubyte alpha = 255); // load from file and upload to GPU
  
  void load(const std::string & BMP_Name, glm::u8vec3 color, GLubyte alpha);
  
  void bind(GLuint mixMode);   // GL_REPLACE, GL_MODULATE, GL_ADD, ...
  void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); };

  GLuint width() const { return mWidth; };
  GLuint height() const { return mHeight; };
  
  void setWrap(GLuint wp);  // GL_REPEAT, GL_CLAMP 

  void loadColorBuffer();

  void save(const std::string & BMP_NAME);
protected:

  void init();
  
  GLuint mWidth = 0;
  GLuint mHeight = 0;
  GLuint mId = 0;
  
};

//-------------------------------------------------------------------------

#endif //_H_Texture_H_

