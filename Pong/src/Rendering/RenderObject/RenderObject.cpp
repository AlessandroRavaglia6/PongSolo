#include "RenderObject.h"

#include "VertexBufferManager.h"

RenderObject::RenderObject(Program& program, VertexArrayObject& vao, VertexBufferObject& vboSharedElement, VertexBufferObject& vboSharedIndex,
	VertexBufferObject& vboInstanced, VertexAttribArray& vertexAttribShared, VertexAttribArray& vertexAttribInstanced)
	: _program(program), _vao(vao), _vboSharedVertex(vboSharedElement), _vboSharedElement(vboSharedIndex), _vboInstanced(vboInstanced), 
	_attributesShared(vertexAttribShared), _attributesInstanced(vertexAttribInstanced), _instanceCount(0), _dataInstancedAttributes({}), _isDataInstancedAttributesChanged(false)
{}

RenderObject::RenderObject(Program& program, VertexArrayObject& vao, VertexBufferObject&& vboSharedElement, VertexBufferObject&& vboSharedIndex,
	VertexBufferObject&& vboInstanced, VertexAttribArray& vertexAttribShared, VertexAttribArray& vertexAttribInstanced)
	: _program(program), _vao(vao), _vboSharedVertex(vboSharedElement), _vboSharedElement(vboSharedIndex), _vboInstanced(vboInstanced),
	_attributesShared(vertexAttribShared), _attributesInstanced(vertexAttribInstanced), _instanceCount(0), _dataInstancedAttributes({}), _isDataInstancedAttributesChanged(false)
{}

VertexBufferObject& RenderObject::GetVboSharedVertex() { return _vboSharedVertex; }
VertexBufferObject& RenderObject::GetVboSharedElement() { return _vboSharedElement;}
VertexBufferObject& RenderObject::GetVboInstanced() { return _vboInstanced; }

void RenderObject::AddAttributeShared(Attribute& attribute) 
{
	_attributesShared.AddAttribute(attribute);
}

void RenderObject::AddAttributeInstanced(Attribute& attribute)
{
	_attributesInstanced.AddAttribute(attribute);
}

void RenderObject::EnableVertexAttributes()
{
	_attributesShared.EnableInstanced(_vao, _vboSharedVertex, 0);
	//_attributesShared.EnableInstanced(_vao, _vboSharedElement, 0);  // Error -> should load the elements
	_attributesInstanced.EnableInstanced(_vao, _vboInstanced, 1);
}

DrawCall* RenderObject::GenDrawCall(GLenum mode, GLsizei elementCount, GLenum type, const void* indices)
{
	return new DrawCallDrawElementsInstanced(mode, elementCount, type, indices, _instanceCount);
}

RenderObjectInstance& RenderObject::GenRenderObjectInstance() 
{
	int size = _attributesInstanced.VertexSize();
	int offset = _instanceCount * size;
	RenderObjectInstance res{ offset, _dataInstancedAttributes, size, _isDataInstancedAttributesChanged };

	++_instanceCount;
	_dataInstancedAttributes.resize(_dataInstancedAttributes.size() + size);

	/*
	for (int i = 0; i < size; ++i)
	{
		_dataInstancedAttributes.push_back(0);
	}/**/

	return res;
}

void RenderObject::UpdateInstancedAttributes() 
{
	if (_isDataInstancedAttributesChanged) 
	{
		VertexBufferManager::BindVBO(_vboInstanced);
		_vboInstanced.BufferData(_dataInstancedAttributes.size(), &_dataInstancedAttributes[0], GL_DYNAMIC_DRAW);
		_isDataInstancedAttributesChanged = false;
	}
}