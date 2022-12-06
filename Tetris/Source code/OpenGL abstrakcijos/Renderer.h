#pragma once

#include <GL/glew.h>
#include <signal.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#ifdef _MSC_VER
#define DEBUG_BREAK __debugbreak()
#else
#define DEBUG_BREAK  raise(SIGTRAP)
#endif

#define ASSERT(x) if (!(x)) DEBUG_BREAK;

#define GLCall(x) GLClearError();\
 x;\
 ASSERT(GLLogCall(#x, __FILE__, __LINE__))
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)const;
};