#ifndef _RENDER_OBJECT
#define _RENDER_OBJECT

#include <GL/glew.h>

#include "Attribute.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "VertexAttribArray.h"
#include "../Program.h"
#include "../Renderer/DrawCall/DrawCall.h"
#include "../Renderer/DrawCall/DrawCallDrawElementsInstanced.h"

#include "RenderObjectInstance.h"

#include <vector>

class RenderObject 
{
private:
	Program _program;

	VertexArrayObject _vao;
	VertexBufferObject _vboSharedVertex;
	VertexBufferObject _vboSharedElement;
	VertexBufferObject _vboInstanced;

	VertexAttribArray& _attributesShared;
	VertexAttribArray& _attributesInstanced;

	GLsizei _instanceCount;

	std::vector<char> _dataInstancedAttributes;  // _attributesInstanced.VertexSize() = attribute size
	bool _isDataInstancedAttributesChanged;
	// vector<Uniform> _uniforms

public:
	RenderObject() = default;
	RenderObject(const RenderObject& other) = default;
	//RenderObject(RenderObject&& other) = default;
	RenderObject& operator=(const RenderObject&) = default;
	//RenderObject& operator=(RenderObject&&) = default;
	~RenderObject() = default;

	RenderObject(Program& program, VertexArrayObject& vao, VertexBufferObject& vboSharedVertex, VertexBufferObject& vboSharedElement, 
		VertexBufferObject& vboInstanced, VertexAttribArray& attributeShared, VertexAttribArray& attributeInstanced);

	RenderObject(Program& program, VertexArrayObject& vao, VertexBufferObject&& vboSharedVertex, VertexBufferObject&& vboSharedElement,
		VertexBufferObject&& vboInstanced, VertexAttribArray& attributeShared, VertexAttribArray& attributeInstanced);


	VertexBufferObject& GetVboSharedVertex();
	VertexBufferObject& GetVboSharedElement();
	VertexBufferObject& GetVboInstanced();


	void AddAttributeShared(Attribute& attribute);
	void AddAttributeInstanced(Attribute& attribute);

	void EnableVertexAttributes();

	DrawCall* GenDrawCall(GLenum mode, GLsizei elementCount, GLenum type, const void* indices);

	RenderObjectInstance& GenRenderObjectInstance();

	void UpdateInstancedAttributes();
};

#endif