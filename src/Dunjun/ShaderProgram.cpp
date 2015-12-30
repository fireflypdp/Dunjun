#include <Dunjun/ShaderProgram.h>

#include <fstream>

namespace Dunjun
{
	///////////////////////////////////////////////////////////

	INTERNAL std::string stringFromFile(const std::string & filename)
	{
		std::ifstream file; // RAII - resource acquisition is initialization
		file.open(filename.c_str(), std::ios::in | std::ios::binary);

		std::string output;
		std::string line;

		if (!file.is_open())
		{
			std::runtime_error(std::string("Failed to open file: ") + filename);
		}
		else
		{
			while (file.good())
			{
				getline(file, line);
				output.append(line + "\n");
			}
		}

		file.close();
		return output;
	}

	///////////////////////////////////////////////////////////

	ShaderProgram::ShaderProgram()
		: m_object(0)
		, m_isLinked(false)
		, m_errorLog()
	{
		m_object = glCreateProgram();
	}

	///////////////////////////////////////////////////////////

	ShaderProgram::~ShaderProgram() 
	{
		if (m_object)
			glDeleteProgram(m_object);
	}

	///////////////////////////////////////////////////////////

	bool ShaderProgram::AttachShaderFromFile(ShaderType type, const std::string & filename) 
	{
		std::string source = stringFromFile(filename);
		return AttachShaderFromMemory(type, source);
	}

	///////////////////////////////////////////////////////////

	bool ShaderProgram::AttachShaderFromMemory(ShaderType type, const std::string & source) 
	{
		if (!m_object)
			m_object = glCreateProgram();

		const char * shaderSource = source.c_str();

		GLuint shader;
		if (type == ShaderType::Vertex)
			shader = glCreateShader(GL_VERTEX_SHADER);
		else if (type == ShaderType::Fragment)
			shader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(shader, 1, &shaderSource, nullptr);
		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			std::string msg("Compile failure in shader:\n");
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			char * strInfoLog = new char[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, nullptr, strInfoLog);
			msg.append(strInfoLog);
			msg.append("\n");
			delete[] strInfoLog;

			m_errorLog.append(msg);

			glDeleteShader(shader);
			return false;
		}

		glAttachShader(m_object, shader);
		
		return true;
	}

	///////////////////////////////////////////////////////////

	void ShaderProgram::Use() const 
	{
		if (IsInUse())
			return;

		glUseProgram(m_object);
	}

	///////////////////////////////////////////////////////////

	bool ShaderProgram::IsInUse() const
	{
		GLint currentProgram = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

		return (currentProgram == static_cast<GLint>(m_object));
	}

	///////////////////////////////////////////////////////////

	void ShaderProgram::StopUsing() const 
	{
		if (!IsInUse())
			return;

		glUseProgram(0);
	}

	///////////////////////////////////////////////////////////

	bool ShaderProgram::Link()
	{
		if (!IsLinked())
		{
			glLinkProgram(m_object);

			GLint status;
			glGetProgramiv(m_object, GL_LINK_STATUS, &status);
			if (status == GL_FALSE)
			{
				std::string msg("Program linking failure:\n");
				GLint infoLogLength;
				glGetProgramiv(m_object, GL_INFO_LOG_LENGTH, &infoLogLength);
				char * strInfoLog = new char[infoLogLength + 1];
				glGetProgramInfoLog(m_object, infoLogLength, nullptr, strInfoLog);
				msg.append(strInfoLog);
				msg.append("\n");
				delete[] strInfoLog;
				m_errorLog.append(msg);

				glDeleteProgram(m_object);
				m_object = 0;

				m_isLinked = false;
				return m_isLinked;
			}
			m_isLinked = true;
		}
		
		return m_isLinked;
	}

	///////////////////////////////////////////////////////////

	bool ShaderProgram::IsLinked() const
	{
		return m_isLinked;
	}

	///////////////////////////////////////////////////////////

	void ShaderProgram::BindAttributeLocation(GLuint location, const GLchar * name)
	{
		glBindAttribLocation(m_object, location, name);
	}

	///////////////////////////////////////////////////////////

	GLint ShaderProgram::GetAttribLocation(const GLchar * name) 
	{
		return glGetAttribLocation(m_object, name);
	}

	///////////////////////////////////////////////////////////

	GLint ShaderProgram::GetUniformLocation(const GLchar * name)
	{
		return glGetUniformLocation(m_object, name);
	}

	///////////////////////////////////////////////////////////

	void ShaderProgram::SetUniform(const GLchar * name, f32 x)
	{
		if (!IsInUse())
			Use();

		glUniform1f(GetUniformLocation(name), x);
	}

	///////////////////////////////////////////////////////////

	void ShaderProgram::SetUniform(const GLchar * name, f32 x, f32 y) 
	{
		glUniform2f(GetUniformLocation(name), x, y);
	}

	///////////////////////////////////////////////////////////

	void ShaderProgram::SetUniform(const GLchar * name, f32 x, f32 y, f32 z)
	{
		glUniform3f(GetUniformLocation(name), x, y, z);
	}

	///////////////////////////////////////////////////////////

	void ShaderProgram::SetUniform(const GLchar * name, f32 x, f32 y, f32 z, f32 w)
	{
		glUniform4f(GetUniformLocation(name), x, y, z, w);
	}

	///////////////////////////////////////////////////////////

	void ShaderProgram::SetUniform(const GLchar * name, u32 x)
	{
		glUniform1ui(GetUniformLocation(name), x);
	}

	///////////////////////////////////////////////////////////

	void ShaderProgram::SetUniform(const GLchar * name, s32 x) 
	{
		glUniform1i(GetUniformLocation(name), x);
	}

	///////////////////////////////////////////////////////////

	void ShaderProgram::SetUniform(const GLchar * name, bool x) 
	{
		glUniform1i(GetUniformLocation(name), static_cast<s32>(x));
	}

	///////////////////////////////////////////////////////////
}
