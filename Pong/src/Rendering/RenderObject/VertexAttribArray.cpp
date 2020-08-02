#include "VertexAttribArray.h"

#include "VertexBufferManager.h"
#include "VertexArrayManager.h"

const std::vector<Attribute>& VertexAttribArray::GetAttributes() { return _attributes; }

void VertexAttribArray::AddAttribute(Attribute& attribute)
{
	_attributes.push_back(attribute);
	_stride += attribute.GetFullAttributeSize();
}

void VertexAttribArray::AddAttribute(Attribute&& attribute)
{
	_attributes.push_back(attribute);
	_stride += attribute.GetFullAttributeSize();
}

void VertexAttribArray::Enable(VertexArrayObject& vao, VertexBufferObject& vbo)
{
	unsigned int offset{};

	VertexArrayManager::BindVAO(vao);
	VertexBufferManager::BindVBO(vbo);

	for (Attribute& attrib : _attributes)
	{
		glVertexAttribPointer(attrib.GetIndex(), attrib.GetSize(), attrib.GetType(), attrib.GetNormalized(), _stride, (void*)offset);
		glEnableVertexAttribArray(attrib.GetIndex());

		offset += attrib.GetFullAttributeSize();
	}
};

void VertexAttribArray::EnableInstanced(VertexArrayObject& vao, VertexBufferObject& vbo, GLsizei instanceCount)
{
	unsigned int offset{};

	VertexArrayManager::BindVAO(vao);
	VertexBufferManager::BindVBO(vbo);

	for (Attribute& attrib : _attributes)
	{
		glVertexAttribPointer(attrib.GetIndex(), attrib.GetSize(), attrib.GetType(), attrib.GetNormalized(), _stride, (void*)offset);
		glEnableVertexAttribArray(attrib.GetIndex());
		glVertexAttribDivisor(attrib.GetIndex(), instanceCount);

		offset += attrib.GetFullAttributeSize();
	}
};

GLsizei VertexAttribArray::VertexSize() { return _stride; }