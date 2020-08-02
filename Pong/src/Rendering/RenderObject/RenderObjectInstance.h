#ifndef _RENDER_OBJECT_INSTANCE
#define _RENDER_OBJECT_INSTANCE

#include <vector>

class RenderObjectInstance
{
	friend class RenderObject;

private:
	int _offset;
	std::vector<char>& _dataInstancedAttributes;
	int _size;
	bool& _parentDataState;

private:
	RenderObjectInstance(int offset,std::vector<char>& dataInstancedAttributes, int size, bool& dataState);
	//RenderObjectInstance(int);

public:
	RenderObjectInstance() = delete;
	RenderObjectInstance(const RenderObjectInstance& other) = default;
	~RenderObjectInstance() = default;

	void UpdateAttributes(const void* attributeData);
};

#endif