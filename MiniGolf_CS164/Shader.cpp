#include "Shader.h"

#include <fstream>
#include <iostream>

void Shader::Enable()
{
	glUseProgram(program);
}

void Shader::PrintLog(char* label, GLint obj)
{
	int infoLogLength = 0;
	int maxLength;

	if (glIsShader(obj)) {
		glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &maxLength);
	} else {
		glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &maxLength);
	}

	char* infoLog = new char[maxLength];

	if (glIsShader(obj)) {
		glGetShaderInfoLog(obj, maxLength, &infoLogLength, infoLog);
	} else {
		glGetProgramInfoLog(obj, maxLength, &infoLogLength, infoLog);
	}

	if (infoLogLength > 0) {
		std::ofstream fout("log.txt");
		fout << label << infoLog << std::endl;
		fout.close();
		// TODO: Replace with a console log
	}

	delete infoLog;
}

void Shader::BindArrayObjects()
{
	vertex = glGetAttribLocation(program, "pos");
	color = glGetAttribLocation(program, "color");
	normal = glGetAttribLocation(program, "norm");
}

void Shader::BindUniforms()
{
	mat_camera = glGetUniformLocation(program, "camera");
	mat_modelTransform = glGetUniformLocation(program, "transform");
	mat_projection = glGetUniformLocation(program, "proj");
	mat_normal = glGetUniformLocation(program, "normalMat");

	sun = glGetUniformLocation(program, "L_p");
	ambient = glGetUniformLocation(program, "ambient");
	eye = glGetUniformLocation(program, "eye");
}

void Shader::BindBufferObjects()
{
	GLuint bufs[4];
	glGenBuffers(4, bufs);

	vertexBuffer = bufs[0];
	colorBuffer = bufs[1];
	indexBuffer = bufs[2];
	normalBuffer = bufs[3];
}

bool Shader::Init(char* vsFile, char* fragFile)
{
	GLint vSrc = SetShaderSource(vsFile, GL_VERTEX_SHADER),
		  fSrc = SetShaderSource(fragFile, GL_FRAGMENT_SHADER);

	if (vSrc < 0 || fSrc < 0)
	{
		// Log that shit happened
		return false;
	}

	program = glCreateProgram();

	glCompileShader(vSrc);
	PrintLog("Vertex compile log: ", vSrc);
	glAttachShader(program, vSrc);

	glCompileShader(fSrc);
	PrintLog("Fragment compile log: ", fSrc);
	glAttachShader(program, fSrc);

	glLinkProgram(program);

	BindArrayObjects();
	BindUniforms();
	BindBufferObjects();

	return true;
}

GLint Shader::SetShaderSource(char* file, GLenum type)
{
	// Open the specified file
	std::ifstream fin(file);
	if (fin.fail())
	{
		// Log file open failure
		return -1;
	}

	// Count the file size
	fin.seekg(0, std::ios::end);
	std::streamoff count = fin.tellg();

	// Read the file
	char* data = nullptr;
	if (count)
	{
		fin.seekg(std::ios::beg); // go back to beginning of file
#pragma warning( suppress : 4244 )
		data = new char[count + 1]; // allocate memory for the file contents
		fin.read(data, count); // read the file
		
		// std::ifstream appends garbage for some reason. What the fuck microsoft?
		// This block of code finds the last closed block in
		// the GLSL source and plugs the source right after that,
		// such that OGL does not try to compile garbage.
#pragma warning( suppress : 4244 )
		for (int i = count; i > 0; i--)
		{
			if (data[i] == '}')
			{ 
				data[i + 1] = '\0';
				break;
			}
		}
	}
	fin.close();

	// Create the shader using the newly obtained data
	GLint s = glCreateShader(type);
	glShaderSource(s, 1, const_cast<const char**>(&data), 0);
	delete[] data; // clean up
	return s;
}