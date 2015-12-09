#include "Dunjun/Image.h"

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>

namespace Dunjun
{
	/////////////////////////////////////////////////////////

	Image::Image()
		: m_format(ImageFormat::NONE)
		, m_width(0)
		, m_height(0)
		, m_pixels(nullptr)
	{
	}

	/////////////////////////////////////////////////////////

	Image::Image(u32 width, u32 height, ImageFormat format, const u08 * pixels)
		: m_format(ImageFormat::NONE)
		, m_width(0)
		, m_height(0)
		, m_pixels(nullptr)
	{
		LoadFromMemory(width, height, format, pixels);
	}

	/////////////////////////////////////////////////////////

	Image::Image(const Image & other)
		: m_format(ImageFormat::NONE)
		, m_width(0)
		, m_height(0)
		, m_pixels(nullptr)
	{
		LoadFromMemory(other.m_width, other.m_height, other.m_format, other.m_pixels);
	}

	/////////////////////////////////////////////////////////

	Image& Image::operator=(const Image & other)
	{
		LoadFromMemory(other.m_width, other.m_height, other.m_format, other.m_pixels);
		return *this;
	}

	/////////////////////////////////////////////////////////

	Image::~Image()
	{
		if (m_pixels)
		{
			delete[] m_pixels;
		}
	}

	/////////////////////////////////////////////////////////

	bool Image::LoadFromFile(const char * filename)
	{
		int width, height, format;
		u08 * pixels = stbi_load(filename, &width, &height, &format, 0);

		if (!pixels)
		{
			std::cerr << stbi_failure_reason() << std::endl;
			return false;
		}

		LoadFromMemory(width, height, static_cast<ImageFormat>(format), pixels);

		stbi_image_free(pixels);

		if (m_pixels)
			return true;

		return false;
	}

	/////////////////////////////////////////////////////////

	bool Image::LoadFromMemory(u32 width, u32 height, ImageFormat format, const u08 * pixels)
	{
		if (width == 0)
		{
			std::cerr << "zero width image" << std::endl;
			return false;
		}
		if (height == 0)
		{
			std::cerr << "zero height image" << std::endl;
			return false;
		}

		m_width = width;
		m_height = height;
		m_format = format;

		usize imageSize = width * height * static_cast<usize>(format);
		if (m_pixels)
			delete[] m_pixels;

		m_pixels = new u08[imageSize];
		if (pixels != nullptr)
		{
			std::memcpy(m_pixels, pixels, imageSize);
		}
		return true;
	}

	/////////////////////////////////////////////////////////

	u08 * Image::GetPixel(u32 column, u32 row) const
	{
		if (column >= m_width || row >= m_height)
			return nullptr;

		return m_pixels + ((row*m_width) + column) * static_cast<usize>(m_format);
	}

	/////////////////////////////////////////////////////////

	void Image::SetPixel(u32 column, u32 row, const u08 * pixel)
	{
		if (column >= m_width || row >= m_height)
			return;

		u08 * p = GetPixel(column, row);
		std::memcpy(p, pixel, static_cast<usize>(m_format));
	}

	/////////////////////////////////////////////////////////

	void Image::FlipVertically()
	{
		usize pitch = m_width * static_cast<usize>(m_format);
		u32 halfRows = m_height / 2;
		u08 * rowBuffer = new u08[pitch];

		for (u08 i = 0; i < halfRows; ++i)
		{
			u08 * row = m_pixels + (i * m_width) * static_cast<usize>(m_format);
			u08 * opposite = m_pixels + ((m_height - i - 1) * m_width) * static_cast<usize>(m_format);

			std::memcpy(rowBuffer, row, pitch);
			std::memcpy(row, opposite, pitch);
			std::memcpy(opposite, rowBuffer, pitch);
		}

		delete[] rowBuffer;
	}

	/////////////////////////////////////////////////////////

	void Image::Rotate90CCW()
	{
		// not supported yet
		assert(false);
	}

	/////////////////////////////////////////////////////////

	void Image::copyRectFromImage(const Image & src, u32 srcCol, u32 srcRow, u32 destCol, u32 destRow, u32 width, u32 height)
	{
		// not supported yet
		assert(false);
	}

	/////////////////////////////////////////////////////////

	ImageFormat Image::GetFormatFromGLEnum(GLint format)
	{
		switch (format)
		{
		case GL_RGB:
		case GL_SRGB:
			return ImageFormat::RGB;
		case GL_RGBA:
		case GL_SRGB_ALPHA:
			return ImageFormat::RGBA;
		case GL_LUMINANCE:
			return ImageFormat::GREYSCALE;
		case GL_LUMINANCE_ALPHA:
			return ImageFormat::GREYSCALEALPHA;
		default:
			throw std::runtime_error("bad format");
			return ImageFormat::NONE;
		}
	}

	/////////////////////////////////////////////////////////

	GLint Image::GetGLEnumFromFormat(ImageFormat format, bool srgb)
	{
		switch (format)
		{
		case ImageFormat::RGB:
			return srgb ? GL_SRGB : GL_RGB;
		case ImageFormat::RGBA:
			return srgb ? GL_SRGB_ALPHA : GL_RGBA;
		case ImageFormat::GREYSCALE:
			return GL_LUMINANCE;
		case ImageFormat::GREYSCALEALPHA:
			return GL_LUMINANCE_ALPHA;
		default:
			throw std::runtime_error("bad format");
			return 0;
		}
	}

	/////////////////////////////////////////////////////////

} // namespace Dunjun