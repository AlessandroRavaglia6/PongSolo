#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "Rendering/Shader/ShaderType.h"
#include "Rendering/Shader/Shader.h"
#include "Rendering/Program.h"

#include "Rendering/Renderer/Renderer.h"
#include "Rendering/Shader/ShaderSourceCode.h"

#include "Utilities/ShaderBuilder.h"
#include "Utilities/FileReader.h"

#include "Rendering/Model/Model.h"
#include "Rendering/Model/ModelLoader_STL.h"

#include "Rendering/RenderObject/VertexArrayObject.h"
#include "Rendering/RenderObject/VertexBufferObject.h"

#include "Rendering/RenderObject/VertexBufferManager.h"
#include "Rendering/RenderObject/VertexArrayManager.h"


class QuadPrefab
{
private:
	VertexArrayObject _vao;
	GLsizei _elementsSize;

public:
	QuadPrefab() = default;

	GLsizei GetElementsSize() { return _elementsSize; }

	VertexArrayObject& GetVao() { return _vao; }

	RenderObject CreateQuad(Program& program, VertexAttribArray& renderObjectAttributesShared, VertexAttribArray& renderObjectAttributesInstanced)
	{
		// ----------------------------------------> Build the RenderObject
		_vao = { VertexArrayManager::GenVAO() };
		VertexArrayManager::BindVAO(_vao);

	
		RenderObject renderObject 
		{
			program, _vao,
			VertexBufferManager::GenVBO(GL_ARRAY_BUFFER),
			VertexBufferManager::GenVBO(GL_ELEMENT_ARRAY_BUFFER),
			VertexBufferManager::GenVBO(GL_ARRAY_BUFFER),
			renderObjectAttributesShared,
			renderObjectAttributesInstanced
		};

		renderObject.EnableVertexAttributes();

		// -----------------------------------------------------> Set up the buffers
		GLfloat vertices[]  // a quad
		{
			-0.2f, -0.2f, 0.0f,		1.0f, 0.0f, 0.0f,
			 0.2f, -0.2f, 0.0f,		1.0f, 1.0f, 1.0f,
			 0.2f,  0.2f, 0.0f,		0.0f, 0.0f, 1.0f,
			-0.2f,  0.2f, 0.0f,		1.0f, 1.0f, 1.0f
		};
		VertexBufferManager::BindVBO(renderObject.GetVboSharedVertex());
		renderObject.GetVboSharedVertex().BufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);

		GLuint elements[]  // a quad = 2 triangles
		{
			0, 2, 1,
			2, 0, 3
		};
		VertexBufferManager::BindVBO(renderObject.GetVboSharedElement());
		renderObject.GetVboSharedElement().BufferData(sizeof(elements), elements, GL_STATIC_DRAW);

		_elementsSize = sizeof(elements) / sizeof(GLuint);

		return std::move(renderObject);
	}
};

class TrianglePrefab
{
private:
	VertexArrayObject _vao;
	GLsizei _elementsSize;

public:
	TrianglePrefab() = default;

	GLsizei GetElementsSize() { return _elementsSize; }

	VertexArrayObject& GetVao() { return _vao; }

	RenderObject CreateTriangle(Program& program, VertexAttribArray& renderObjectAttributesShared, VertexAttribArray& renderObjectAttributesInstanced)
	{
		// ----------------------------------------> Build the RenderObject
		_vao = { VertexArrayManager::GenVAO() };
		VertexArrayManager::BindVAO(_vao);

		RenderObject renderObject
		{
			program, _vao,
			VertexBufferManager::GenVBO(GL_ARRAY_BUFFER),
			VertexBufferManager::GenVBO(GL_ELEMENT_ARRAY_BUFFER),
			VertexBufferManager::GenVBO(GL_ARRAY_BUFFER),
			renderObjectAttributesShared,
			renderObjectAttributesInstanced
		};

		renderObject.EnableVertexAttributes();

		// -----------------------------------------------------> Set up the buffers
		GLfloat vertices[]  // a quad
		{
			-0.1f, -0.1f, 0.0f,		1.0f, 0.0f, 0.0f,
			 0.1f, -0.1f, 0.0f,		1.0f, 1.0f, 1.0f,
			 0.0f,  0.2f, 0.0f,		0.0f, 0.0f, 1.0f,
		};
		VertexBufferManager::BindVBO(renderObject.GetVboSharedVertex());
		renderObject.GetVboSharedVertex().BufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);

		GLuint elements[]  // a quad = 2 triangles
		{
			0, 2, 1,
		};
		VertexBufferManager::BindVBO(renderObject.GetVboSharedElement());
		renderObject.GetVboSharedElement().BufferData(sizeof(elements), elements, GL_STATIC_DRAW);

		_elementsSize = sizeof(elements) / sizeof(GLuint);

		return std::move(renderObject);
	}
};






// VertexAttribSerializer Test
#include "FileManagement/VertexAttribSerializer.h"

class HeadPrefab
{
private:
	VertexArrayObject _vao;
	GLsizei _elementsSize;

public:
	HeadPrefab() = default;

	GLsizei GetElementsSize() { return _elementsSize; }

	VertexArrayObject& GetVao() { return _vao; }

	RenderObject CreateHead(Program& program, VertexAttribArray& renderObjectAttributesShared, VertexAttribArray& renderObjectAttributesInstanced, std::string& modelFileName)
	{
		// ----------------------------------------> Build the RenderObject
		_vao = { VertexArrayManager::GenVAO() };
		VertexArrayManager::BindVAO(_vao);

		RenderObject renderObject
		{
			program, _vao,
			VertexBufferManager::GenVBO(GL_ARRAY_BUFFER),
			VertexBufferManager::GenVBO(GL_ELEMENT_ARRAY_BUFFER),
			VertexBufferManager::GenVBO(GL_ARRAY_BUFFER),
			renderObjectAttributesShared,
			renderObjectAttributesInstanced
		};

		renderObject.EnableVertexAttributes();

		// -----------------------------------------------------> Set up the buffers
		
		// TODO change with a code to get the data in a generic way
		std::vector<char> vertices;
	
		Model model{};
		model.load_data(new ModelLoader_STL(model), modelFileName);
		model.AverageNormalsElem();
		std::vector<char*> attribData{};
		attribData.push_back((char*)&(model.GetPositions()[0])); // Won't work just yet.. the data are not specified for a DrawElement call
		attribData.push_back((char*)&(model.GetNormals()[0]));
		vertices = VertexAttribSerializer::Serialize(renderObjectAttributesShared, attribData, model._numIndex);

		VertexBufferManager::BindVBO(renderObject.GetVboSharedVertex());
		renderObject.GetVboSharedVertex().BufferData(vertices.size(), &vertices[0], GL_STATIC_DRAW);


		// TODO change with a code to get the data in a generic way

		VertexBufferManager::BindVBO(renderObject.GetVboSharedElement());
		renderObject.GetVboSharedElement().BufferData(model.GetIndices().size() * sizeof(GLint), &(model.GetIndices()[0]), GL_STATIC_DRAW);

		_elementsSize = model.GetNumIndices();// / sizeof(GLuint);

		return std::move(renderObject);
	}
};
// End VertexAttribSerializer Test





//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


int winWidth = 1200;
int winHeight = 600;


int main(void)
{
	GLFWwindow* window;

	// Init GLFW
	if (!glfwInit()) { return -1; }

	// Create a window and it's OpenGl context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(winWidth, winHeight, "Pong", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Make the window context current
	glfwMakeContextCurrent(window);

	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		std::cout << "ERROR: %s" << glewGetErrorString(GlewInitResult) << std::endl;
		return -1;
	}





	// Enable culling and depth testing
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);





	//Program prog{};
	Renderer renderer{};

	ShaderBuilder shaderBuilder{};


	Shader vShader{ shaderBuilder.AddShaderType(ShaderType::VERTEX).AddShaderSourceCode("ShaderFiles/shader.vert").BuildShader() };
	Shader fShader{ shaderBuilder.AddShaderType(ShaderType::FRAGMENT).AddShaderSourceCode("ShaderFiles/shader.frag").BuildShader() };

	Program program{ renderer.AddShaderToProgram(vShader).AddShaderToProgram(fShader).BuildProgram() };



	Shader vSh{ shaderBuilder.AddShaderType(ShaderType::VERTEX).AddShaderSourceCode("ShaderFiles/Phong.vert").BuildShader() };
	Shader fSh{ shaderBuilder.AddShaderType(ShaderType::FRAGMENT).AddShaderSourceCode("ShaderFiles/Phong.frag").BuildShader() };

	Program headProgram{ renderer.AddShaderToProgram(vSh).AddShaderToProgram(fSh).BuildProgram() };


	// ----------------------------------------> Build the Attribuets Array that i'm going to use;
	VertexAttribArray renderObjectAttributesShared{};		// VAO need to be bound
	VertexAttribArray renderObjectAttributesInstanced{};	// VAO need to be bound

	Attribute position{ 0, GL_FLOAT, 3, GL_FALSE, sizeof(GLfloat) * 3 };
	Attribute color{ 1, GL_FLOAT, 3, GL_FALSE, sizeof(GLfloat) * 3 };
	renderObjectAttributesShared.AddAttribute(position);
	renderObjectAttributesShared.AddAttribute(color);

	Attribute translate{ 2, GL_FLOAT, 2, GL_FALSE, sizeof(GLfloat) * 2 };
	renderObjectAttributesInstanced.AddAttribute(translate);



	// Head
	Attribute normal{ 1, GL_FLOAT, 3, GL_FALSE, sizeof(GLfloat) * 3 };
	VertexAttribArray headAttributesShared{};
	headAttributesShared.AddAttribute(position);
	headAttributesShared.AddAttribute(normal);

	Attribute rotate{ 3, GL_FLOAT, 2, GL_FALSE, sizeof(GLfloat) * 2 };
	VertexAttribArray headAttributeInstanced{};
	headAttributeInstanced.AddAttribute(translate);
	headAttributeInstanced.AddAttribute(rotate);
	// -------------------------------------------------------------------------------------------->


	GLfloat translation[2];
	struct TransRot 
	{
		GLfloat xTra;
		GLfloat yTra;
		GLfloat xRot;
		GLfloat yRot;
		TransRot() = default;
	};

	TransRot headInstancedData{};


	// ----------------------------------------------> Create Heads
	HeadPrefab headPrefab{};
	std::string fileName = "3DModels/Head.stl";
	RenderObject head{ headPrefab.CreateHead(headProgram, headAttributesShared, headAttributeInstanced, fileName) };
	// -----------------------> Head Instances
	RenderObjectInstance head_1{ head.GenRenderObjectInstance() };
	RenderObjectInstance head_2{ head.GenRenderObjectInstance() };
	RenderObjectInstance head_3{ head.GenRenderObjectInstance() };

	//for (int i = 0; i < 100; ++i) { head.GenRenderObjectInstance(); };

	headInstancedData = { -0.5f, -0.3f, 0.0f, 0.0f };
	head_1.UpdateAttributes((void*)&headInstancedData);

	headInstancedData = {  0.5f, -0.4f, 0.0f, 0.0f };
	head_2.UpdateAttributes((void*)&headInstancedData);

	headInstancedData = {  0.2f, -0.6f, 0.0f, 0.0f };
	head_3.UpdateAttributes((void*)&headInstancedData);/**/

	head.UpdateInstancedAttributes();

	renderer.AddRenderObjectDrawCall
	(
		headProgram,
		headPrefab.GetVao(),
		head.GenDrawCall(GL_TRIANGLES, headPrefab.GetElementsSize(), GL_UNSIGNED_INT, 0)
	);




	// ----------------------------------------------> Create Quads
	QuadPrefab quadPrefab{};

	RenderObject renderObject{quadPrefab.CreateQuad(program, renderObjectAttributesShared, renderObjectAttributesInstanced)};

	// ----------------------------------------------------> Generate RenderObjectsInstances and set their data
	RenderObjectInstance roi_1{ renderObject.GenRenderObjectInstance() };
	RenderObjectInstance roi_2{ renderObject.GenRenderObjectInstance() };
	RenderObjectInstance roi_3{ renderObject.GenRenderObjectInstance() };
	RenderObjectInstance roi_4{ renderObject.GenRenderObjectInstance() };

	translation[0] = -0.5f;
	translation[1] = -0.5f;
	roi_1.UpdateAttributes((void*)translation);

	translation[0] =  0.5f;
	translation[1] = -0.5f;
	roi_2.UpdateAttributes((void*)translation);

	translation[0] =  0.5f;
	translation[1] =  0.5f;
	roi_3.UpdateAttributes((void*)translation);

	translation[0] = -0.5f;
	translation[1] =  0.5f;
	roi_4.UpdateAttributes((void*)translation);

	renderObject.UpdateInstancedAttributes();

	renderer.AddRenderObjectDrawCall
	(
		program,
		quadPrefab.GetVao(),
		renderObject.GenDrawCall(GL_TRIANGLES, quadPrefab.GetElementsSize(), GL_UNSIGNED_INT, 0)
	);



	// -------------------------------------------------------> Create Triangles
	TrianglePrefab trianglePrefab{};

	RenderObject triangle{ trianglePrefab.CreateTriangle(program, renderObjectAttributesShared, renderObjectAttributesInstanced) };

	// ----------------------------------------------------> Generate RenderObjectsInstances and set their data
	RenderObjectInstance tri_1{ triangle.GenRenderObjectInstance() };
	RenderObjectInstance tri_2{ triangle.GenRenderObjectInstance() };
	RenderObjectInstance tri_3{ triangle.GenRenderObjectInstance() };
	RenderObjectInstance tri_4{ triangle.GenRenderObjectInstance() };

	translation[0] =  0.0f;
	translation[1] = -0.5f;
	tri_1.UpdateAttributes((void*)translation);

	translation[0] =  0.0f;
	translation[1] =  0.5f;
	tri_2.UpdateAttributes((void*)translation);

	translation[0] = 0.5f;
	translation[1] = 0.0f;
	tri_3.UpdateAttributes((void*)translation);

	translation[0] = -0.5f;
	translation[1] =  0.0f;
	tri_4.UpdateAttributes((void*)translation);

	triangle.UpdateInstancedAttributes();

	renderer.AddRenderObjectDrawCall
	(
		program,
		trianglePrefab.GetVao(),
		triangle.GenDrawCall(GL_TRIANGLES, trianglePrefab.GetElementsSize(), GL_UNSIGNED_INT, 0)
	);




	unsigned int frameCount = 0;
	double secondCount = 0.0;
	translation[1] = -0.5;
	double currentFrame = glfwGetTime();
	double deltaTime;
	double lastFrame = currentFrame;
	double speed = 1.0;

	GLfloat rotation = 0.0f;




	// Test Camera
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)winWidth / (float)winHeight, 0.1f, 5.0f);

	unsigned int UBO;
	glGenBuffers(1, &UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, 64, NULL, GL_STATIC_DRAW); // allocate 152 bytes of memory
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// Link the buffer to the binding point (the shader need to be linked
	// too and in this example it has been done inside the shader)
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO);

	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, 64, &(projectionMatrix));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);




	// Loop until the user close the window
	while (!glfwWindowShouldClose(window))
	{
		// ***** RENDER HERE *****

		// deltaTime 
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Frame count
		secondCount += deltaTime;
		++frameCount;
		if (secondCount > 1.0)
		{
			secondCount = 0.0;
			std::cout << "fps: " << frameCount << std::endl;
			frameCount = 0;
		}

		glClearColor(0.0f, 0.0f, 0.0f, false);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		translation[0] += (float)(speed * deltaTime);
		roi_1.UpdateAttributes(translation);
		renderObject.UpdateInstancedAttributes();


		
		rotation += (float)(speed * deltaTime);
		headInstancedData = { -0.5f, -0.3f, rotation, 0.0f };
		head_1.UpdateAttributes(&headInstancedData);

		headInstancedData = { 0.5f, -0.4f, 0.0f, rotation };
		head_2.UpdateAttributes(&headInstancedData);

		head.UpdateInstancedAttributes();


		// Rendering
		renderer.Render();
		// Rendering


		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}