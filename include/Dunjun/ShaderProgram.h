#ifndef DUNJUN_SHADERPROGRAM_H
#define DUNJUN_SHADERPROGRAM_H

#include <Dunjun/Common.h>
#include <Dunjun/NonCopyable.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Dunjun
{
	enum class ShaderType
	{
		Vertex,
		Fragment,
	};

	class ShaderProgram : public NonCopyable
	{
	public:
		ShaderProgram();
		virtual ~ShaderProgram();

		b08 AttachShaderFromFile(ShaderType type, const std::string & filename);
		b08 AttachShaderFromMemory(ShaderType type, const std::string & source);

		void Use() const;
		b08 IsInUse() const;
		void StopUsing() const;

		b08 Link();
		b08 IsLinked() const;

		void BindAttributeLocation(GLuint location, const GLchar * name);
		
		GLint GetAttribLocation(const GLchar * name);
		GLint GetUniformLocation(const GLchar * name);

		void SetUniform(const GLchar * name, f32 x);
		void SetUniform(const GLchar * name, f32 x, f32 y);
		void SetUniform(const GLchar * name, f32 x, f32 y, f32 z);
		void SetUniform(const GLchar * name, f32 x, f32 y, f32 z, f32 w);
		void SetUniform(const GLchar * name, u32 x);
		void SetUniform(const GLchar * name, s32 x);
		void SetUniform(const GLchar * name, b08 x);

		inline GLuint GetObject() const { return m_object; }
		inline const std::string & GetErrorLog() const { return m_errorLog; }

	private:
		GLuint m_object;
		b08 m_isLinked;
		std::string m_errorLog;
	};
} // namespace Dunjun

#endif//DUNJUN_SHADERPROGRAM_H
