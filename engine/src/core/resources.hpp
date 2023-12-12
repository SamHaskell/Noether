#pragma once

#include "core/defines.hpp"

#include <unordered_map>

#include "graphics/shader.hpp"
#include "graphics/textures.hpp"
#include "graphics/materials.hpp"
#include "graphics/mesh.hpp"

namespace Noether {
    class UUID {
        public:
            UUID();
            UUID(u64 id) : m_UUID(id) {};

            operator u64() const { return m_UUID; }
        private:
            u64 m_UUID;
    };
}

namespace std {    
	template<> struct hash<Noether::UUID> {
		size_t operator()(Noether::UUID const& uuid) const {
			return (u64)uuid;
		}
	};
}

namespace Noether {
    template <typename T>
    class Resource {
        friend class ResourceManager;
        public:
            Resource(const Resource<T>& resource) : m_UUID(resource.m_UUID) {};
        private:
            Resource() = default;
            Resource(UUID id) : m_UUID(id) {};
            
            inline UUID GetUUID() { return m_UUID; }

        private:
            UUID m_UUID;
    };

    class ResourceManager {
        public:
            ResourceManager() = default;
            ~ResourceManager();

            Resource<Shader> GetShader(const std::string& path);
            Resource<Shader> LoadShader(const std::string& path);
            Shader& Access(const Resource<Shader> handle);

            Resource<Texture2D> GetTexture2D(const std::string& path);
            Resource<Texture2D> LoadTexture2D(const std::string& path);
            Texture2D& Access(const Resource<Texture2D> handle);

            Resource<Mesh> GetMesh(const std::string& path);
            Resource<Mesh> LoadMesh(const std::string& path);
            Mesh& Access(const Resource<Mesh> handle);

        private:
            std::unordered_map<UUID, Shader*> m_ShaderPool;
            std::unordered_map<UUID, Texture2D*> m_TexturePool;
            std::unordered_map<UUID, Mesh*> m_MeshPool;

            std::unordered_map<std::string, UUID> m_IdentifierLookup;
    };
};

