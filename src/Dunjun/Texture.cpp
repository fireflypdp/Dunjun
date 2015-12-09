#include "Dunjun/Common.h"
#include "Dunjun/Texture.h"

namespace Dunjun
{
	/////////////////////////////////////////////////////////

	Texture::Texture()
		: m_object(0)
		, m_width(0)
		, m_height(0)
	{
		glGenTextures(1, &m_object);
	}

	/////////////////////////////////////////////////////////

	Texture::Texture(const Image & image, GLint minMagFilter, GLint wrapMode)
		: m_object(0)
		, m_width((GLfloat)image.GetWidth())
		, m_height((GLfloat)image.GetHeight())
	{
		glGenTextures(1, &m_object);

		if (!LoadFromImage(image, minMagFilter, wrapMode))
			throw std::runtime_error("Image failed to load");
	}

	/////////////////////////////////////////////////////////

	bool Texture::LoadFromFile(const char * filename, GLint minMagFilter, GLint wrapMode)
	{
		Image image;
		if (!image.LoadFromFile(filename))
			return false;
		image.FlipVertically();

		return LoadFromImage(image, minMagFilter, wrapMode);
	}

	/////////////////////////////////////////////////////////

	bool Texture::LoadFromImage(const Image & image, GLint minMagFilter, GLint wrapMode)
	{
		m_width = (GLfloat)image.GetWidth();
		m_height = (GLfloat)image.GetHeight();

		glGenTextures(1, &m_object);
		glBindTexture(GL_TEXTURE_2D, m_object);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFilter);

		glTexImage2D(GL_TEXTURE_2D, 0, Image::GetGLEnumFromFormat(image.GetFormat(), true), (GLsizei)m_width, (GLsizei)m_height, 0,
			Image::GetGLEnumFromFormat(image.GetFormat(), false), GL_UNSIGNED_BYTE, image.GetPixelPtr());

		return true;
	}

	/////////////////////////////////////////////////////////

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_object);
	}

	/////////////////////////////////////////////////////////

	void Texture::Bind(GLuint position)
	{
		if (position > 31)
		{
			std::cerr << "Textures can only be bound to position [0..31]\n" <<
				"Will bind to position [31]" << std::endl;
			position = 31;
		}

		glActiveTexture(GL_TEXTURE0 + position);
		glClientActiveTexture(GL_TEXTURE0 + position);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_object ? m_object : 0);
		glDisable(GL_TEXTURE_2D);
	}

	/////////////////////////////////////////////////////////
} // namespace Dunjun
