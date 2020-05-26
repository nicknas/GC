//#pragma once
#ifndef _H_Pixmap32RGBA_H
#define _H_Pixmap32RGBA_H

//#include <Windows.h>
//#include <gl/GL.h>

#include <GL/freeglut.h>
#include <string>
#ifdef _WIN32
#include <glm.hpp>
#else
#include <glm/glm.hpp>
#endif


class Pixmap32RGBA {   
public:
   
	typedef glm::u8vec4 rgba_color;  
 
   Pixmap32RGBA() noexcept : data_{ nullptr }, width_{ 0 }, height_{ 0 } {}

   Pixmap32RGBA(Pixmap32RGBA && pixmap) noexcept;
   Pixmap32RGBA & operator=(Pixmap32RGBA && pixmap) noexcept;

   Pixmap32RGBA(const Pixmap32RGBA & pixmap) = delete;
   Pixmap32RGBA & operator=(const Pixmap32RGBA & pixmap) = delete;

   ~Pixmap32RGBA() noexcept { free(); }
      
   void load_bmp24BGR(const std::string & file_name);  // throw(std::ios_base::failure, std::exception);
   void save_bmp24BGR(const std::string & file_name) const;  // throw(std::ios_base::failure);
   
   void reserve(GLsizei width, GLsizei height);  // throw(std::exception, std::bad_alloc);
   
   void set_alpha(GLubyte alpha) noexcept;
   void set_colorkey_alpha(glm::u8vec3 colorKey, GLubyte alpha) noexcept;

   Pixmap32RGBA clone();  // throw(std::exception, std::bad_alloc);
   
   void free() noexcept;

   GLsizei width() const noexcept { return width_; }

   GLsizei height() const noexcept { return height_; }

   const rgba_color* data() const noexcept { return data_; }

   rgba_color* data()  noexcept { return data_; }

   bool is_null() const noexcept { return (data_ == nullptr); }
   
   const rgba_color & pixel(const GLsizei x, const GLsizei y) const noexcept
   { return data_[y * width_ + x]; }

   void set_pixel(const GLsizei x, const GLsizei y, const rgba_color & rgba) noexcept
   { data_[y * width_ + x] = rgba; }

protected:

   void load_headers(std::ifstream & stream, unsigned int & width, unsigned int & height) const; // throw(std::ios_base::failure);
   void save_headers(std::ofstream & stream) const noexcept;

   void row_bgr_rgba(char* rowAux, unsigned int r) noexcept;
   void row_rgba_bgr(char* rowAux, unsigned int r) const noexcept;

private:

	rgba_color * data_;
	GLsizei   width_;
	GLsizei   height_;

};
   
#endif //_H_Pixmap32RGBA_H
