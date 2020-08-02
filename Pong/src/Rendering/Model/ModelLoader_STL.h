#ifndef _MODEL_LOADER_STL
#define _MODEL_LOADER_STL

#include "ModelLoader.h"
#include "Model.h"

#include <string>

class ModelLoader_STL : public ModelLoader
{
private:
	Model& model;

public:
	ModelLoader_STL(Model& model) : model(model) {}

	void load(const std::string& fileName)
	{
		const int facet_size = 50;
		unsigned int num_facets = 0;

		std::ifstream file(fileName, std::ios::in | std::ios::binary);
		if (!file.is_open())
		{
			std::cout << "Error: file.open() [" << fileName << "]" << std::endl;
			return;
		}

		// Read the header (80 bytes)
		char header[80];
		file.read(header, 80);
		std::cout << header << std::endl;

		// Read the first 4 byte (an integer containing the number of facet)
		file.read((char*)(&num_facets), 4);
		std::cout << "Model_Loader_STL.load(): " << num_facets << std::endl;

		model._numVertices = num_facets * 3;
		//model._positions.
		model._positions = std::make_unique<GLfloat*>(new GLfloat[model._numVertices * 3]);
		model._normals = std::make_unique<GLfloat*>(new GLfloat[model._numVertices * 3]);
		//model._positions = new GLfloat[model._numVertices * 3];
		//model._normals = new GLfloat[model._numVertices * 3]; // data

		// Read the facet data into a Triangle array
		char buffer[facet_size];
		for (unsigned int i = 0; i < num_facets; ++i)
		{
			file.read((char*)buffer, facet_size);

			int offset = 0;
			for (int j = 0; j < 3; ++j) // Normal
			{
				(*model._normals.get())[(i * 9) + j] = ((GLfloat*)buffer)[offset];
				(*model._normals.get())[(i * 9) + 3 + j] = (*model._normals.get())[(i * 9) + j];
				(*model._normals.get())[(i * 9) + 6 + j] = (*model._normals.get())[(i * 9) + j];

				//model._normals[(i * 9) + j] = ((GLfloat*)buffer)[offset];
				//model._normals[(i * 9) + 3 + j] = model._normals[(i * 9) + j];
				//model._normals[(i * 9) + 6 + j] = model._normals[(i * 9) + j];
				offset++;
			}
			for (int j = 0; j < 3; ++j) // Vertices
			{
				for (int k = 0; k < 3; ++k)
				{
					(*model._positions.get())[(i * 9) + (j * 3) + k] = ((GLfloat*)buffer)[offset];

					//model._positions[(i * 9) + (j * 3) + k] = ((GLfloat*)buffer)[offset];
					offset++;
				}
			}
		}

		file.close();
	}
};

#endif