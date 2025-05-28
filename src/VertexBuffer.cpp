#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size):m_stride(0), m_vertexNum(size){
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &m_id));
}

void VertexBuffer::Bind() const{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

void VertexBuffer::Unbind() const{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}


const std::vector<LayoutElement>& VertexBuffer::GetLayout() const {
    return m_layoutSets;
}


unsigned int VertexBuffer::GetStride() const {
    return m_stride;
}

unsigned int VertexBuffer::GetVertexNum() const {
    return m_vertexNum;
}