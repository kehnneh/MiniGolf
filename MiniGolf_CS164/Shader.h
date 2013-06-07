#pragma once

#include <gl\glew.h>
#include <gl\freeglut.h>

/// Defines an OpenGL shader and its associated vertex array and buffer objects
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

  /// Initializes the shader
	bool Init(char* vsFile, char* fsFile);

  /// Tells OpenGL to use this shader
	void Enable();

private:
	void BindUniforms();
	void BindArrayObjects();
	void BindBufferObjects();
	GLint SetShaderSource(char* filename, GLenum type);
	void PrintLog(char* label, GLint obj);
};

