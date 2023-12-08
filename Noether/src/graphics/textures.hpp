#pragma once

#include "core/defines.hpp"

namespace Noether {
    class Texture2D {
        public:
            static std::shared_ptr<Texture2D> Create(const std::string& path);
            static std::shared_ptr<Texture2D> Create(i32 width, i32 height);
            virtual ~Texture2D() = default;

            virtual void Bind(u32 unit = 0) = 0;
            virtual void Unbind() = 0;
    };  

    struct CubeMapData {
        std::string Paths[6];
    };

    class TextureCube {
        public:
            static std::shared_ptr<TextureCube> Create(const CubeMapData& data);
            virtual ~TextureCube() = default;    

            virtual void Bind() = 0;
            virtual void Unbind() = 0;
    };
};