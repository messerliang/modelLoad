#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "GL_Error.h"

struct LayoutElement{
	unsigned int count;			// ���ݵ�ά�ȣ��� 2ά��3ά���� 4 ά
	unsigned int type;			// ����if����ʾ�� GL_Float ���� int ���� byte 
	unsigned char isNormalized;	// �Ƿ���Ҫ��ʼ��
	unsigned int size;			// count ��Ԫ�صĴ�С

	LayoutElement(unsigned int c = 0, unsigned int type = 0, unsigned char norm = false, unsigned int sz=0) :
		count(c), type(type), isNormalized(norm), size(sz){}
};

class VertexBuffer
{
private:

	std::vector<LayoutElement> m_layoutSets;
	unsigned int m_id;
	unsigned int m_stride;


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
	
	
	template<typename T>
	void Push(unsigned int count, unsigned char isNorm) {
		unsigned int sz = sizeof(T);
		_ASSERTE(sz >= 1 && sz <= 4);
		sz = sz * count;
		m_layoutSets.emplace_back(count, MapTypeToGLEnum<T>(), isNorm, sz);
		m_stride += sz;
	}

};

