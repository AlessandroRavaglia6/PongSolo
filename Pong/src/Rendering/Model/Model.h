#ifndef _MODEL
#define _MODEL

#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <unordered_map>
#include "ModelLoader.h"

// Delete this includes
#include <GL/glew.h>


enum Model_Mode { FLAT, SMOOTH };

struct VertexBuffer  // Change to unique_ptr<GLfloat> ??
{
public:
	GLfloat* data;

	VertexBuffer(int size)
	{
		data = new GLfloat[size];
	}

	~VertexBuffer() { delete(data); }
};

struct Vec3
{
	GLfloat value[3];
};

inline void avg(Vec3& v_1, Vec3& v_2, Vec3& res)
{
	res.value[0] = (v_1.value[0] + v_2.value[0]) / (GLfloat)2.0f;
	res.value[1] = (v_1.value[1] + v_2.value[1]) / (GLfloat)2.0f;
	res.value[2] = (v_1.value[2] + v_2.value[2]) / (GLfloat)2.0f;
}

struct Triple
{
	GLfloat x;
	GLfloat y;
	GLfloat z;

	Triple() : x(0.0f), y(0.0f), z(0.0f) {}
	Triple(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}

	bool operator==(const Triple& other) const
	{
		return (x == other.x && y == other.y && z == other.z);
	}
};

template<>
struct std::hash<Triple>
{
	std::size_t operator()(const Triple& k) const
	{
		using std::size_t;
		using std::hash;
		using std::string;

		// Compute individual hash values for first,
		// second and third and combine them using XOR
		// and bit shifting:

		return ((hash<GLfloat>()(k.x)
			^ (hash<GLfloat>()(k.y) << 1)) >> 1)
			^ (hash<GLfloat>()(k.z) << 1);
	}
};

struct NormDataPacked
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	unsigned int n;
	GLint index;

	NormDataPacked() : x(0.0f), y(0.0f), z(0.0f), n((unsigned int)0), index(0) {}
	NormDataPacked(GLfloat x, GLfloat y, GLfloat z, unsigned int n, GLint index) : x(x), y(y), z(z), n(n), index(index) {}
};

class Model
{
public:
	unsigned int _numVertices;
	std::unique_ptr<GLfloat*> _positions;
	std::unique_ptr<GLfloat*> _normals;

	std::vector<GLint> _elementIndices;
	std::vector<GLfloat> _elementPositions;
	std::vector<GLfloat> _elementNormals;

	std::unordered_map<GLint, Triple> _indexPositionMap;
	GLint _numIndex;

public:
	Model() : _numVertices(0), _positions({ nullptr }), _normals({ nullptr }), _indexPositionMap({}), _numIndex(0) {}

	void load_data(ModelLoader* loader, const std::string& filename)    // Defenetly not the right way
	{
		loader->load(filename);
	}

	///////////////////////////////////////////////////////////////////////////////////////
	class VN_Map     // Just do the math where you need to do it
	{
	public:
		std::unordered_map<Triple, NormDataPacked> map;

		VN_Map(Model& model)
		{
			GLint lastIndex = 0;
			unsigned int num_vert = model.GetNumVertices();
			model._elementIndices = std::vector<GLint>(model.GetNumVertices());
			for (unsigned int i = 0; i < num_vert; ++i)
			{
				Triple curr_vert(model.GetPositionAt((i * 3) + 0),
					model.GetPositionAt((i * 3) + 1),
					model.GetPositionAt((i * 3) + 2));

				if (map.count(curr_vert) == 0)
				{
					map[curr_vert].x = model.GetNormalAt((i * 3) + 0);
					map[curr_vert].y = model.GetNormalAt((i * 3) + 1);
					map[curr_vert].z = model.GetNormalAt((i * 3) + 2);
					map[curr_vert].n = 1;
					map[curr_vert].index = lastIndex;
					
					model._indexPositionMap[lastIndex].x = curr_vert.x;
					model._indexPositionMap[lastIndex].y = curr_vert.y;
					model._indexPositionMap[lastIndex].z = curr_vert.z;

					++lastIndex;
				}
				else
				{
					map[curr_vert].x += model.GetNormalAt((i * 3) + 0);
					map[curr_vert].y += model.GetNormalAt((i * 3) + 1);
					map[curr_vert].z += model.GetNormalAt((i * 3) + 2);
					map[curr_vert].n++;
				}
				model._elementIndices[i] = map[curr_vert].index;
			}
			model._numIndex = lastIndex;
		}
	};
	///////////////////////////////////////////////////////////////////////////////////////

	void AverageNormals()   // This one maybe a good one to keep (but move the VN_Map inside it)
	{
		VN_Map map = VN_Map(*this);

		NormDataPacked curr_norm;
		Triple curr_vert;
		for (unsigned int i = 0; i < _numVertices; ++i)
		{
			curr_vert.x = (*_positions.get())[(i * 3) + 0];
			curr_vert.y = (*_positions.get())[(i * 3) + 1];
			curr_vert.z = (*_positions.get())[(i * 3) + 2];

			//curr_vert.x = _positions[(i * 3) + 0];
			//curr_vert.y = _positions[(i * 3) + 1];
			//curr_vert.z = _positions[(i * 3) + 2];

			curr_norm = map.map[curr_vert];

			(*_normals.get())[(i * 3) + 0] = curr_norm.x / (GLfloat)curr_norm.n;
			(*_normals.get())[(i * 3) + 1] = curr_norm.y / (GLfloat)curr_norm.n;
			(*_normals.get())[(i * 3) + 2] = curr_norm.z / (GLfloat)curr_norm.n;

			//_normals[(i * 3) + 0] = curr_norm.x / (GLfloat)curr_norm.n;
			//_normals[(i * 3) + 1] = curr_norm.y / (GLfloat)curr_norm.n;
			//_normals[(i * 3) + 2] = curr_norm.z / (GLfloat)curr_norm.n;
		}
	}



	void AverageNormalsElem()   // This one maybe a good one to keep (but move the VN_Map inside it)
	{
		VN_Map map = VN_Map(*this);

		_elementPositions = std::vector<GLfloat>(_numIndex * 3);
		_elementNormals = std::vector<GLfloat>(_numIndex * 3);

		for (int i = 0; i < _numIndex; ++i) 
		{
			_elementPositions[(i * 3)] = _indexPositionMap[i].x;
			_elementPositions[(i * 3) + 1] = _indexPositionMap[i].y;
			_elementPositions[(i * 3) + 2] = _indexPositionMap[i].z;

			_elementNormals[(i * 3)] = map.map[_indexPositionMap[i]].x / 3.0f;
			_elementNormals[(i * 3) + 1] = map.map[_indexPositionMap[i]].y / 3.0f;
			_elementNormals[(i * 3) + 2] = map.map[_indexPositionMap[i]].z / 3.0f;
		}
	}

	unsigned int GetNumElements() { return _numIndex; };
	unsigned int GetNumIndices() { return _numVertices; }
	std::vector<GLint>& GetIndices() { return _elementIndices; }
	std::vector<GLfloat>& GetPositions() { return _elementPositions; }
	std::vector<GLfloat>& GetNormals() { return _elementNormals; }



	~Model()
	{
		//delete[](_positions); // DEBUG: togli le quadre ///////////////////////////////////
		//delete[](_normals);
	}

	unsigned int GetNumVertices() const
	{
		return _numVertices;
	}

	GLfloat GetPositionAt(unsigned int index) const { return (*_positions.get())[index]; }
	GLfloat GetNormalAt(unsigned int index) const { return (*_normals.get())[index]; }

	const GLfloat* GetPositionsArray()    // use it in combination with VertexBufferObject -> buferData
	{
		return *_positions.get();
	}

	const GLfloat* GetNormalsArray()     // use it in combination with VertexBufferObject -> buferData
	{
		return *_normals.get();
	}
};

#endif