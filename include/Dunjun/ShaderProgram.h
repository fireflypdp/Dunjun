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

		bool AttachShaderFromFile(ShaderType type, const std::string & filename);
		bool AttachShaderFromMemory(ShaderType type, const std::string & source);

		void Use() const;
		bool IsInUse() const;
		void StopUsing() const;

		bool Link();
		bool IsLinked() const;

		void BindAttributeLocation(GLuint location, const GLchar * name);
		
		GLint GetAttribLocation(const GLchar * name);
		GLint GetUniformLocation(const GLchar * name);

		void SetUniform(const GLchar * name, f32 x);
		void SetUniform(const GLchar * name, f32 x, f32 y);
		void SetUniform(const GLchar * name, f32 x, f32 y, f32 z);
		void SetUniform(const GLchar * name, f32 x, f32 y, f32 z, f32 w);
		void SetUniform(const GLchar * name, u32 x);
		void SetUniform(const GLchar * name, s32 x);
		void SetUniform(const GLchar * name, bool x);

		inline GLuint GetObject() const { return m_object; }
		inline const std::string & GetErrorLog() const { return m_errorLog; }

	private:
		GLuint m_object;
		bool m_isLinked;
		std::string m_errorLog;
	};
} // namespace Dunjun

#endif//DUNJUN_SHADERPROGRAM_H
