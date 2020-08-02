#include "VertexAttribSerializer.h"

//#include <iostream>

std::vector<char> VertexAttribSerializer::Serialize(VertexAttribArray& attributes, std::vector<char*>& attributesData, unsigned int numVertices)
{
	unsigned int vertexSize = 0;
	std::vector<GLsizei> attribSizes{};
	for (const Attribute& attrib : attributes.GetAttributes())
	{
		vertexSize += attrib.GetFullAttributeSize();
		attribSizes.push_back(attrib.GetFullAttributeSize());
	}

	std::vector<char> serializedData(numVertices * vertexSize);
	char* offset = &(serializedData[0]);

	int numAttributes = attribSizes.size();
	int attribSize = 0;

	int count = 0;
	for (int i = 0; i < numVertices; ++i)
	{
		for (int j = 0; j < numAttributes; ++j)
		{
			attribSize = attribSizes[j];
			for (int k = 0; k < attribSize; k++)
			{
				*offset = (attributesData[j])[(i * attribSize) + k];
				++offset;
				//std::cout << count << std::endl; ++count;
			}
		}
	}

	return std::move(serializedData);
}