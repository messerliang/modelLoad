#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GL_Error.h"


class IndexBuffer
{
private:
	unsigned int m_id;
	unsigned int m_count;
public:
	IndexBuffer(const unsigned int* index, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned int GetCount() const;
};

