#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "GL_Error.h"

struct LayoutElement{
	unsigned int count;			// 数据的维度，是 2维、3维还是 4 维
	unsigned int type;			// 类型if。表示是 GL_Float 还是 int 还是 byte 
	unsigned char isNormalized;	// 是否需要初始化
	unsigned int size;			// count 个元素的大小

	LayoutElement(unsigned int c = 0, unsigned int type = 0, unsigned char norm = false, unsigned int sz=0) :
		count(c), type(type), isNormalized(norm), size(sz){}
};

class VertexBuffer
{
private:

	std::vector<LayoutElement> m_layoutSets;
	unsigned int m_id;
	unsigned int m_stride;
	unsigned int m_vertexNum;


	template<typename T>
	static unsigned int MapTypeToGLEnum() {
		if(std::is_same_v<T, float>)    return GL_FLOAT;
		if(std::is_same_v<T, int>)      return GL_INT;
		if(std::is_same_v<T, GLubyte>)  return GL_UNSIGNED_BYTE;
		
		_ASSERT(false);
		return 0;
		
	}

public:

	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();


	void Bind() const;
	void Unbind() const;
	const std::vector<LayoutElement>& GetLayout() const;
	unsigned int GetStride() const;
	unsigned int GetVertexNum() const;
	
	
	template<typename T>
	void Push(unsigned int count, unsigned char isNorm) {
		unsigned int sz = sizeof(T);
		_ASSERTE(sz >= 1 && sz <= 4);
		sz = sz * count;
		m_layoutSets.emplace_back(count, MapTypeToGLEnum<T>(), isNorm, sz);
		m_stride += sz;
	}

};

