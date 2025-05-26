#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GL_Error.h"
#include "VertexBuffer.h"

class VertexArray
{


private:
	unsigned int m_id;
public:
	VertexArray();
	~VertexArray();
	
	void Bind()const;
	void Unbind()const;

	void AddBuffer(const VertexBuffer& vBuf);
};

