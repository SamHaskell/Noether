#pragma once

#include "core/defines.hpp"
#include <vector>

namespace Noether {

    using Index = u32;

    enum class BufferElementType {
        None,
        Int, Int2, Int3, Int4,
        Float, Float2, Float3, Float4,
        Mat2, Mat3, Mat4, Bool
    };

    inline u32 get_buffer_element_size(BufferElementType type) {
        switch(type) {
            case BufferElementType::Int:
                return 4;
            case BufferElementType::Int2:
                return 8;
            case BufferElementType::Int3:
                return 12;
            case BufferElementType::Int4:
                return 16;
            case BufferElementType::Float:
                return 4;
            case BufferElementType::Float2:
                return 8;
            case BufferElementType::Float3:
                return 12;
            case BufferElementType::Float4:
                return 16;
            case BufferElementType::Mat2:
                return 16;
            case BufferElementType::Mat3:
                return 36;
            case BufferElementType::Mat4:
                return 64;
            case BufferElementType::Bool:
                return 4;
            default:
                return 0;
        }
    }

    struct BufferElement {
        BufferElement() = default;
        BufferElement(BufferElementType type, const std::string& name, bool normalised = false);
        BufferElementType Type;
        u32 Size;
        u32 Offset;
        bool Normalised;
        std::string Name;
    };

    class BufferLayout {
        public:
            BufferLayout() = default;
            BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) { Invalidate(); }
            std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
            std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
            std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
            std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
            inline u32 GetStride() const { return m_Stride; }
        private:
            void Invalidate();
            std::vector<BufferElement> m_Elements;
            u32 m_Stride;
    };

    class VertexBuffer {
        public:
            static std::shared_ptr<VertexBuffer> Create(const void* data, u32 size);
            static std::shared_ptr<VertexBuffer> Create(u32 size);
            virtual ~VertexBuffer() = default;
            inline u32 GetVertexCount() const { return m_VertexCount; }
            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;
            virtual void SetData(const void* data, u32 size) const = 0;
        protected:
            u32 m_VertexCount;
    };

    class IndexBuffer {
        public:
            static std::shared_ptr<IndexBuffer> Create(const Index* data, u32 count);
            virtual ~IndexBuffer() = default;
            inline u32 GetIndexCount() const { return m_IndexCount; }
            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;
        protected:
            u32 m_IndexCount;
    };

    class VertexArray {
        public:
            static std::shared_ptr<VertexArray> Create(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer, const BufferLayout& layout);
            virtual ~VertexArray() = default;
            inline BufferLayout GetLayout() const { return m_Layout; }
            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;
            inline u32 GetIndexCount() const { return m_IndexBuffer->GetIndexCount(); }
        protected:
            BufferLayout m_Layout;
            std::shared_ptr<VertexBuffer> m_VertexBuffer;
            std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}