#include "Renderer.h"

#include "../../PreprocessorSettings.h"
#ifdef _STD_OUT
#include <iostream>
#endif

#include "../RenderObject/VertexArrayManager.h"

Renderer::Renderer(const Renderer& r)
{
	#ifdef _STD_OUT
	std::cout << "Renderer_Copy_const" << std::endl;
	#endif
}

Renderer::Renderer() : _drawCallsToRender({}), _tempShaderSet({}) {}


Renderer::~Renderer() 
{
	for (std::pair<Program, std::vector<RenderCallInfo>> elem : _drawCallsToRender)
	{
		for (RenderCallInfo info : elem.second)
		{
			info.drawCall->~DrawCall();
		}
	}
}

Renderer& Renderer::AddShaderToProgram(const Shader& shader)
{
	_tempShaderSet.insert(shader.GetId());
	return *this;
}

void Renderer::AddRenderObjectDrawCall(Program& program, VertexArrayObject& vao, DrawCall* drawCall)
{
	// Not checking for replicas
	_drawCallsToRender[program].push_back({ vao, drawCall });
}

void Renderer::Render() 
{
	for (const std::pair<const Program&, std::vector<RenderCallInfo>>& elem : _drawCallsToRender)
	{
		elem.first.Use();
		for (const RenderCallInfo& info: elem.second)
		{
			VertexArrayManager::BindVAO(info.vao);
			info.drawCall->Draw();
		}
	}
}

Program Renderer::BuildProgram() 
{
	Program p{};

	for (GLuint shaderId : _tempShaderSet) 
	{
		p.AttachShader(shaderId);
	}
	p.Link();

	_tempShaderSet.clear();
	return static_cast<Program&&>(p);
}