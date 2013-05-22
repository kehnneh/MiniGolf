#pragma once

#include <gl\glew.h>
#include <gl\freeglut.h>

class Shader
{
public:
	// Vertex Array Objects
	GLint
		program,
		mat_camera,
		mat_modelTransform,
		mat_projection,
		mat_normal,
		vertex,
		color,
		normal,
		sun,
		ambient,
		eye;

	GLuint
		// Vertex Buffer Objects for OpenGL. Data gets pushed into these.
		vertexBuffer,
		colorBuffer,
		normalBuffer,
		indexBuffer;

	Shader()
		: program(-1),
		  mat_camera(-1),
		  mat_modelTransform(-1),
		  mat_projection(-1),
		  mat_normal(-1),
		  vertex(-1),
		  color(-1),
		  normal(-1),
		  sun(-1),
		  ambient(-1),
		  eye(-1),
		  vertexBuffer(-1),
		  colorBuffer(-1),
		  normalBuffer(-1),
		  indexBuffer(-1)
	{}
	~Shader()
	{}

	bool Init(char* vsFile, char* fsFile);
	void Enable();

private:
	void BindUniforms();
	void BindArrayObjects();
	void BindBufferObjects();
	GLint SetShaderSource(char* filename, GLenum type);
	void PrintLog(char* label, GLint obj);
};

