#include "platform/gl/buffers_gl.hpp"
#include "platform/gl/graphicsutils_gl.hpp"

namespace Noether {
    VertexBufferGL::VertexBufferGL(const void* data, u32 size) {
        glGenBuffers(1, &m_RendererID); GL_LOG_ERROR;
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); GL_LOG_ERROR;
        glBufferData(
            GL_ARRAY_BUFFER,
            size,
            data,
            GL_STATIC_DRAW
        ); GL_LOG_ERROR;
        glBindBuffer(GL_ARRAY_BUFFER, 0); GL_LOG_ERROR;
    }

    VertexBufferGL::VertexBufferGL(u32 size) {
        glGenBuffers(1, &m_RendererID); GL_LOG_ERROR;
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); GL_LOG_ERROR;
        glBufferData(
            GL_ARRAY_BUFFER,
            size,
            NULL,
            GL_STATIC_DRAW
        ); GL_LOG_ERROR;
        glBindBuffer(GL_ARRAY_BUFFER, 0); GL_LOG_ERROR;
    }

    VertexBufferGL::~VertexBufferGL() {
        glDeleteBuffers(1, &m_RendererID); GL_LOG_ERROR;
    }

    void VertexBufferGL::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); GL_LOG_ERROR;
    }

    void VertexBufferGL::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0); GL_LOG_ERROR;
    } 

    void VertexBufferGL::SetData(const void* data, u32 size) const {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); GL_LOG_ERROR;
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data); GL_LOG_ERROR;
    }

    IndexBufferGL::IndexBufferGL(const Index* data, u32 count) {
        glGenBuffers(1, &m_RendererID); GL_LOG_ERROR;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); GL_LOG_ERROR;
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            sizeof(Index) * count,
            data,
            GL_STATIC_DRAW
        ); GL_LOG_ERROR;
        m_IndexCount = count;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); GL_LOG_ERROR;
    }

    IndexBufferGL::~IndexBufferGL() {
        glDeleteBuffers(1, &m_RendererID); GL_LOG_ERROR;
    }

    void IndexBufferGL::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); GL_LOG_ERROR;
    }

    void IndexBufferGL::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); GL_LOG_ERROR;
    } 

    VertexArrayGL::VertexArrayGL(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer, const BufferLayout& layout) {
        m_Layout = layout;
        m_VertexBuffer = vertexBuffer;
        m_IndexBuffer = indexBuffer;
        glGenVertexArrays(1, &m_RendererID); GL_LOG_ERROR;
        glBindVertexArray(m_RendererID); GL_LOG_ERROR;
        vertexBuffer->Bind();
        indexBuffer->Bind();
        u32 idx = 0;
        for (const auto& element : m_Layout) {
            glEnableVertexAttribArray(idx); GL_LOG_ERROR;
            glVertexAttribPointer(
                idx,
                get_buffer_element_type_component_count_gl(element.Type),
                get_buffer_element_type_native_gl(element.Type),
                element.Normalised ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                reinterpret_cast<GLvoid*>(element.Offset)); GL_LOG_ERROR;
            idx ++;
        }
        vertexBuffer->Unbind();
        glBindVertexArray(0); GL_LOG_ERROR;
        indexBuffer->Unbind();
    }

    VertexArrayGL::~VertexArrayGL() {
        glDeleteVertexArrays(1, &m_RendererID); GL_LOG_ERROR;
    }

    void VertexArrayGL::Bind() const {
        glBindVertexArray(m_RendererID); GL_LOG_ERROR;
    }

    void VertexArrayGL::Unbind() const {
        glBindVertexArray(0); GL_LOG_ERROR;
    }
}