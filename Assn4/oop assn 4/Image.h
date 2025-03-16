#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <cstdint>
#include <cassert>
#include "SharedPtr.h"

///////////////////////////////////////////////////////////////////////////
// RGB pixel type
//    Usage:
//      - RGB<float> rgb(0.5f, 0.1f, 0.3f);
//        rgb[0] = 0.2f; // or equivalently, rgb.r = 0.2f;
template<typename ValType>
struct RGB
{
	union {
		ValType data[3];
		struct {
			ValType r, g, b;
		};
	};

	RGB() {}
	RGB(ValType r_, ValType g_, ValType b_) : r(r_), g(g_), b(b_) {}

	ValType operator[](int idx) const { return data[idx]; }
	ValType& operator[](int idx) { return data[idx]; }
};

typedef RGB<uint8_t>	RGB8b;
typedef RGB<float>		RGBf;


///////////////////////////////////////////////////////////////////////////
// Image class template
//
template<typename PixelType>
class Image
{
private:
	// ======= ADD CODE HERE IF NEEDED =========
	SharedArray<PixelType> m_buff;
	size_t m_width; 
	size_t m_height; 
	
public:
	////////////////////////////////////////////
	// constructors 
		//default 
	Image() {
		m_buff = nullptr;
		m_width = 0; 
		m_height = 0; 
	}
		//width and height is given 
	Image(size_t _width, size_t _height) {
		m_buff = SharedArray <PixelType>(new PixelType[_width * _height]);
		m_width = _width; 
		m_height = _height; 
	}
		//width, height, and data is given 
	Image(size_t _width, size_t _height, const PixelType& val) {
		m_buff = SharedArray <PixelType>(new PixelType[_width * _height]);
		for (size_t i = 0; i < _width * _height; i++) {
			m_buff[i] = val;
		}
		m_width = _width;
		m_height = _height;
	}
		//copy constructor 
	Image(const Image<PixelType>& img) {
		m_buff = SharedArray <PixelType>(new PixelType[img.m_width * img.m_height]);
		for (size_t i = 0; i < img.m_width * img.m_height; i++) {
			m_buff[i] = img.m_buff[i];
		}
		m_width = img.m_width;
		m_height = img.m_height;
	}
	//destructor
	
	~Image() { }

	////////////////////////////////////////////
	
	// ======= ADD CODE HERE IF NEEDED =========

	////////////////////////////////////////////
	// assignment operator
	
	Image& operator= (const Image <PixelType>& img) {		//can't you use assignment operator in shared ptr 
		if (this != &img) {
			m_buff = SharedArray <PixelType> (new PixelType[img.m_width * img.m_height]);
			for (size_t i = 0; i < img.m_width * img.m_height; i++) {
				m_buff[i] = img.m_buff[i];
			}
			m_width = img.m_width;
			m_height = img.m_height;
		}
		return *this; 
	}

	const Image& operator= (const Image <PixelType>& img) const {		//can't you use assignment operator in shared ptr 
		if (this != &img) {
			m_buff = SharedArray <PixelType>(new PixelType[img.m_width * img.m_height]);
			for (size_t i = 0; i < img.m_width * img.m_height; i++) {
				m_buff[i] = img.m_buff[i];
			}
			m_width = img.m_width;
			m_height = img.m_height;
		}
		return *this;
	}

	////////////////////////////////////////////
	
	// ======= ADD CODE HERE IF NEEDED =========

	////////////////////////////////////////////
	// element access operators

	////////////////////////////////////////////
	PixelType* operator[](int y) { return &m_buff[y * m_width]; }
	const PixelType* operator[](int y) const { return &m_buff[y * m_width]; }

	////////////////////////////////////////////
	// other methods
	////////////////////////////////////////////
	//   - width(), height()
	size_t width() const {
		return m_width; 
	}
	size_t height() const {
		return m_height; 
	}

	
	// ======= ADD CODE HERE IF NEEDED =========
};

// ======= ADD CODE HERE IF NEEDED =========


// Miscellaneous functions
void convert_pixel_type(const Image<RGB8b>& src, Image<RGBf>& dst);
void convert_pixel_type(const Image<RGBf>& src, Image<RGB8b>& dst);

bool load_bmp(const char* path, Image<RGB8b>& img);
bool save_bmp(const char* path, const Image<RGB8b>& img);

#endif
