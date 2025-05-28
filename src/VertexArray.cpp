#include "VertexArray.h"

VertexArray::VertexArray(const VertexBuffer& vbObj, const IndexBuffer& idObj):m_vertexBuffer(vbObj),m_indexBuffer(idObj) {
	GLCall(glGenVertexArrays(1, &m_id));
	GLCall(glBindVertexArray(m_id));
	AddBuffer(m_vertexBuffer);
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
		// ����1������id
		// ����2���������ٸ�����
		// ����3����������
		// ����4���Ƿ��׼��
		// ����5��stride
		// ����6����ǰ������ vertexbuffer ��ƫ�ƣ���λΪ byte
		GLCall(glVertexAttribPointer(i, it.count, it.type, it.isNormalized, vBuf.GetStride(), (void*)offset));
		offset += it.size;
	}
}

void VertexArray::DrawElement(Shader& shader) const {
	shader.Use();
	Bind();
	this->m_indexBuffer.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, m_indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));
}