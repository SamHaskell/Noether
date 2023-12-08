#include "graphics/buffers.hpp"
#include "platform/gl/buffers_gl.hpp"

namespace Noether {
    BufferElement::BufferElement(BufferElementType type, const std::string& name, bool normalised)
        : Type(type),
        Size(get_buffer_element_size(type)),
        Offset(0),
        Normalised(normalised),
        Name(name) {}

    void BufferLayout::Invalidate() {
        m_Stride = 0;
        for (auto& e : m_Elements) { e.Offset = m_Stride, m_Stride += e.Size; }
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void* data, u32 size) {
        return std::make_shared<VertexBufferGL>(data, size);
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::Create(u32 size) {
        return std::make_shared<VertexBufferGL>(size);
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::Create(const Index* data, u32 count) {
        return std::make_shared<IndexBufferGL>(data, count);
    }

    std::shared_ptr<VertexArray> VertexArray::Create(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer, const BufferLayout& layout) {
        return std::make_shared<VertexArrayGL>(vertexBuffer, indexBuffer, layout);
    }
}