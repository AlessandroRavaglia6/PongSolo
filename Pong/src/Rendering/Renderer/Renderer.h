#ifndef _RENDERER
#define _RENDERER

#include "DrawCall/DrawCall.h"
#include "../Program.h"
#include "../Shader/ShaderType.h"
#include "../RenderObject/RenderObject.h"

#include "../RenderObject/VertexArrayObject.h"
#include "../RenderObject/VertexBufferObject.h"

#include <GL/glew.h>
#include <set>
#include <vector>
#include <unordered_map>


class Renderer 
{
private:
	struct RenderCallInfo
	{
		VertexArrayObject& vao;
		DrawCall* drawCall;
	};

	std::unordered_map<Program, std::vector<RenderCallInfo>> _drawCallsToRender;

	std::set<GLuint> _tempShaderSet;

public:
	Renderer();

	Renderer(const Renderer& r);

	~Renderer();

	void Render();

	Renderer& AddShaderToProgram(const Shader& shader);

	void AddRenderObjectDrawCall(Program& program, VertexArrayObject& vao, DrawCall* drawCall);

	Program BuildProgram();
};

#endif