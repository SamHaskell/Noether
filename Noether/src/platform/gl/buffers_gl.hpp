#pragma once

#include "graphics/buffers.hpp"

namespace Noether {
    class VertexBufferGL : public VertexBuffer {
        public:
            VertexBufferGL(const void* data, u32 size);
            VertexBufferGL(u32 size);
            ~VertexBufferGL();
            void Bind() const override;
            void Unbind() const override;
            void SetData(const void* data, u32 size) const override;
        private:
            u32 m_RendererID;
    };

    class IndexBufferGL : public IndexBuffer {
        public:
            IndexBufferGL(const Index* data, u32 count);
            ~IndexBufferGL();
            void Bind() const override;
            void Unbind() const override;
        private:
            u32 m_RendererID;
    };

    class VertexArrayGL : public VertexArray {
        public:
            VertexArrayGL(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer, const BufferLayout& layout);
            ~VertexArrayGL();
            void Bind() const override;
            void Unbind() const override;
        private:
            u32 m_RendererID;
    };
}