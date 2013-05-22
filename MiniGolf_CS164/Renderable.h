#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include "MatrixObject.h"

class Shader;
class Camera;

class Renderable
{
protected:
	unsigned int vertices, indices;

	// The matrix doesn't do anything right now, since the vertices are hard coded. Vertices need to be abstracted such that
	// the transform matrix represents the renderable's orientation. For tiles, the transform matrix should be the center of the tile
	//glm::mat4* transform;

	MatrixObject *transform;

	glm::vec4* colorData;
	glm::vec3* vertexData;
	glm::vec3* normalData;
	unsigned int* indexData;

private:
	GLenum drawMode;

	void BindVertices();
	void BindNormals();
	void BindIndices();
	void BindColors();

	void TriangulateVertices();
	void GenerateNormals();

public:
	Renderable()
		: vertices(0),
		  indices(0),
		  drawMode(GL_TRIANGLES),
		  transform(0),
		  colorData(0),
		  vertexData(0),
		  normalData(0),
		  indexData(0)
	{}
	~Renderable()
	{}

	bool Init(char* filename);
	bool Init(glm::vec3* vertData, unsigned int numVerts);

	void DeInit();

  void Tick();

	void Render(Camera* c);

	void UniformScale(float factor);
	void SetPosition(glm::vec3 pos);
  void Rotation(glm::vec3 eulerAngles);

	virtual void GenerateColor(glm::vec4 const & colorStored);
	
	static void BindShader(Shader* s);

  MatrixObject *Matrix() const;
};
