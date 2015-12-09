#ifndef DUNJUN_TEXTURE_H
#define DUNJUN_TEXTURE_H

#include <Dunjun/Image.h>
#include <Dunjun/NonCopyable.h>
#include <Dunjun/OpenGL.h>

namespace Dunjun
{
	class Texture : public NonCopyable
	{
	public:
		Texture();
		Texture(const Image & image, GLint minMagFilter = GL_LINEAR, GLint wrapMode = GL_CLAMP_TO_EDGE);

		bool LoadFromFile(const char * filename, GLint minMagFilter = GL_LINEAR, GLint wrapMode = GL_CLAMP_TO_EDGE);
		bool LoadFromImage(const Image & image, GLint minMagFilter = GL_LINEAR, GLint wrapMode = GL_CLAMP_TO_EDGE);

		virtual ~Texture();

		void Bind(GLuint position);

		inline GLuint GetObject() const { return m_object; }
		inline GLfloat GetWidth() const { return m_width; }
		inline GLfloat GetHeight() const { return m_height; }

	private:
		GLuint m_object;
		GLfloat m_width;
		GLfloat m_height;
	};
} // namespace Dunjun

#endif//DUNJUN_TEXTURE_H
