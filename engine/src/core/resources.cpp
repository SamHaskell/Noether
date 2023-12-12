#include "core/resources.hpp"
#include "maths/random.hpp"

namespace Noether {
    UUID::UUID() {
        m_UUID = Random::U64();
    }



    ResourceManager::~ResourceManager() {

    }

    Resource<Shader> ResourceManager::GetShader(const std::string& path) {

    }

    Resource<Shader> ResourceManager::LoadShader(const std::string& path) {

    }

    Shader& ResourceManager::Access(const Resource<Shader> handle) {

    }
    
    Resource<Texture2D> ResourceManager::GetTexture2D(const std::string& path) {

    }

    Resource<Texture2D> ResourceManager::LoadTexture2D(const std::string& path) {

    }

    Texture2D& ResourceManager::Access(const Resource<Texture2D> handle) {

    }

    Resource<Mesh> ResourceManager::GetMesh(const std::string& path) {

    }

    Resource<Mesh> ResourceManager::LoadMesh(const std::string& path) {

    }

    Mesh& ResourceManager::Access(const Resource<Mesh> handle) {

    }


};