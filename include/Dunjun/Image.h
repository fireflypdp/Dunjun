#ifndef DUNJUN_IMAGE_H
#define DUNJUN_IMAGE_H

#include <Dunjun/OpenGL.h>
#include <Dunjun/Common.h>

namespace Dunjun
{
	enum class ImageFormat
	{
		NONE = 0,
		GREYSCALE,
		GREYSCALEALPHA,
		RGB,
		RGBA,
	};

	class Image
	{
	public:
		Image();
		Image(u32 width, u32 height, ImageFormat format, const u08 * pixels = nullptr);
		Image(const Image & other);
		Image& operator=(const Image & other);
		~Image();

		bool LoadFromFile(const char * filename);
		bool LoadFromMemory(u32 width, u32 height, ImageFormat format, const u08 * pixels);

		inline u32 GetWidth() const { return m_width; }
		inline u32 GetHeight() const { return m_height; }
		inline ImageFormat GetFormat() const { return m_format; }
		inline u08 * GetPixelPtr() const { return m_pixels; }

		u08 * GetPixel(u32 column, u32 row) const;
		void SetPixel(u32 column, u32 row, const u08 * pixel);

		void FlipVertically();
		void Rotate90CCW();

		void copyRectFromImage(const Image & src, u32 srcCol, u32 srcRow, u32 destCol, u32 destRow, u32 width, u32 height);

		GLOBAL ImageFormat GetFormatFromGLEnum(GLint format);
		GLOBAL GLint GetGLEnumFromFormat(ImageFormat format, bool srgb);

	private:
		ImageFormat m_format;
		u32 m_width;
		u32 m_height;
		u08 * m_pixels;
	};
} // namespace Dunjun

#endif//DUNJUN_IMAGE_H
