#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GL_Error.h"

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray
{


private:
	unsigned int m_id;
	VertexBuffer m_vertexBuffer;
	IndexBuffer m_indexBuffer;
	void AddBuffer(const VertexBuffer& vBuf);

public:
	// 需要使用 vertexBuffer 和 IndexBuffer 来创建 vertexArray
	VertexArray(const VertexBuffer& vbObj, const IndexBuffer& idObj);
	~VertexArray();
	
	void Bind()const;
	void Unbind()const;
	void DrawElement(Shader& shader) const;


};

