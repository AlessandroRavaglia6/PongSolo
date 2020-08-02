#ifndef _VERTEX_ATTRIB_SERIALIZER
#define _VERTEX_ATTRIB_SERIALIZER

#include <GL/glew.h>

#include "../Rendering/RenderObject/VertexAttribArray.h"
#include "../Rendering/RenderObject/Attribute.h"
#include <vector>
#include <memory>

class VertexAttribSerializer 
{
public:
	VertexAttribSerializer() = delete;
	VertexAttribSerializer(const VertexAttribSerializer&) = delete;
	VertexAttribSerializer(VertexAttribSerializer&&) = delete;
	~VertexAttribSerializer() = delete;

	static std::vector<char> Serialize(VertexAttribArray& attributes, std::vector<char*>& attributesData, unsigned int numVertices);
};

#endif