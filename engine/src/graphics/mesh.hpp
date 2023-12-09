#pragma once

#include "core/defines.hpp"
#include "graphics/buffers.hpp"

#include "maths/vector.hpp"
#include "maths/matrix.hpp"

namespace Noether {
    struct Vertex {
        Vec3 Position;
        Vec3 Normal;
        Vec2 TexCoord;
        static BufferLayout GetBufferLayout();
        bool operator==(const Vertex& other) const;
    };

    struct SubMesh {
        u32 VertexBase;
        u32 VertexCount;
        u32 IndexBase;
        u32 IndexCount;
        Mat4 WorldTransform;
        Mat4 LocalTransform;
    };

    class Mesh {
        public:
            Mesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices, const std::vector<SubMesh>& subMeshes);
            ~Mesh();

            static std::shared_ptr<Mesh> Load(const std::string& path);
            static std::shared_ptr<Mesh> Create(const std::vector<Vertex>& vertices, const std::vector<Index>& indices, const Mat4& transform);
            static std::shared_ptr<Mesh> Create(const std::vector<Vertex>& vertices, const std::vector<Index>& indices, const std::vector<SubMesh>& subMeshes);

            inline u32 GetVertexCount() { return m_Vertices.size(); }
            inline u32 GetIndexCount() { return m_Indices.size(); }

            inline const std::shared_ptr<VertexArray>& GetVertexArray() const { return m_VertexArray; }

        private:
            std::string m_Path;
            std::vector<SubMesh> m_SubMeshes;
            std::vector<Vertex> m_Vertices;
            std::vector<Index> m_Indices;
            std::shared_ptr<VertexBuffer> m_VertexBuffer;
            std::shared_ptr<IndexBuffer> m_IndexBuffer;
            std::shared_ptr<VertexArray> m_VertexArray;
    };
};

namespace std {
    template<> struct hash<Noether::Vertex> {
        size_t operator()(Noether::Vertex const& vertex) const {
            return ((hash<Noether::Vec3>()(vertex.Position) ^
                   (hash<Noether::Vec3>()(vertex.Normal) << 1)) >> 1) ^
                   (hash<Noether::Vec2>()(vertex.TexCoord) << 1);
        }
    };
}