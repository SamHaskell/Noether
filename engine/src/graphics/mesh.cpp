#include "graphics/mesh.hpp"

#include "tiny_obj_loader.h"
#include <unordered_map>

namespace Noether {
    bool Vertex::operator==(const Vertex& other) const {
        return (Position == other.Position) && (Normal == other.Normal) && (TexCoord == other.TexCoord);
    }

    BufferLayout Vertex::GetBufferLayout() {
        return BufferLayout({
            {BufferElementType::Float3, "a_Position"},
            {BufferElementType::Float3, "a_Normal"},
            {BufferElementType::Float2, "a_TexCoord"}
        });
    }

    std::shared_ptr<Mesh> Mesh::Load(const std::string& path) {

        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        
        std::string warn;
        std::string err;

        bool load_ok = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());
        if (!load_ok) {
            NT_ERROR("%s", err.c_str());
        }
        NT_INFO("%s", warn.c_str());

        std::vector<Vertex> vertices = {};
        std::vector<Index> indices = {};
        std::unordered_map<Vertex, u32> uniqueVertices {};

        for (const auto& shape : shapes) {
            for (const auto& index : shape.mesh.indices) {
                Vertex vertex = {};

                vertex.Position = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
                };

                vertex.Normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
                };

                vertex.TexCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    attrib.texcoords[2 * index.texcoord_index + 1]
                };

                if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                    vertices.push_back(vertex);
                }
                indices.push_back(uniqueVertices[vertex]); 
            }
        }

        // TODO: Implement submeshing for complex models and rigged models.

        return Mesh::Create(vertices, indices, Matrix4::Identity());
    }

    std::shared_ptr<Mesh> Mesh::Create(const std::vector<Vertex>& vertices, const std::vector<Index>& indices, const Mat4& transform) {
        SubMesh subMesh = {
            .VertexBase = 0,
            .VertexCount = static_cast<u32>(vertices.size()),
            .IndexBase = 0,
            .IndexCount = static_cast<u32>(indices.size()),
            .WorldTransform = transform,
            .LocalTransform = Matrix4::Identity()
        };

        std::vector<SubMesh> subMeshes = {subMesh};
        return std::make_shared<Mesh>(vertices, indices, subMeshes);
    }

    std::shared_ptr<Mesh> Mesh::Create(const std::vector<Vertex>& vertices, const std::vector<Index>& indices, const std::vector<SubMesh>& subMeshes) {
        return std::make_shared<Mesh>(vertices, indices, subMeshes);
    }

    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices, const std::vector<SubMesh>& subMeshes)
        : m_Vertices(vertices), m_Indices(indices), m_SubMeshes(subMeshes) 
    {
        m_VertexBuffer = VertexBuffer::Create(vertices.data(), static_cast<u32>(vertices.size()) * sizeof(Vertex));
        m_IndexBuffer = IndexBuffer::Create(indices.data(), static_cast<u32>(indices.size()));
        m_VertexArray = VertexArray::Create(m_VertexBuffer, m_IndexBuffer, Vertex::GetBufferLayout());
    }

    Mesh::~Mesh() {

    }
};