#include "VertexArray.h"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_id));
	GLCall(glBindVertexArray(m_id));
}
VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_id));
}

void VertexArray::Bind() const{
	GLCall(glBindVertexArray(m_id));
}

void VertexArray::Unbind() const {
	GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vBuf) {
	const std::vector<LayoutElement> layoutSets = vBuf.GetLayout();
	unsigned int offset = 0;
	for (int i = 0; i < layoutSets.size(); ++i) {
		const auto& it = layoutSets[i];
		GLCall(glEnableVertexAttribArray(i));
		// 参数1：属性id
		// 参数2：包含多少个数据
		// 参数3：数据类型
		// 参数4：是否标准化
		// 参数5：stride
		// 参数6：当前属性在 vertexbuffer 的偏移，单位为 byte
		GLCall(glVertexAttribPointer(i, it.count, it.type, it.isNormalized, vBuf.GetStride(), (void*)offset));
		offset += it.size;
	}
}