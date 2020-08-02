#ifndef _MODEL_LOADER
#define _MODEL_LOADER

#include "Model.h"

class ModelLoader
{
public:
	virtual void load(const std::string& fileName) = 0;
};

#endif