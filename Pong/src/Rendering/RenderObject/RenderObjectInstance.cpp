#include "RenderObjectInstance.h"

RenderObjectInstance::RenderObjectInstance(const int offset, std::vector<char>& dataInstancedAttributes, const int size, bool& dataState)
	: _offset(offset), _dataInstancedAttributes(dataInstancedAttributes), _size(size), _parentDataState(dataState) {}

void RenderObjectInstance::UpdateAttributes(const void* attributeData) 
{
	for (unsigned int i = 0; i < _size; ++i) 
	{
		_dataInstancedAttributes[_offset + i] = ((char*)attributeData)[i];
	}
	_parentDataState = true;
}