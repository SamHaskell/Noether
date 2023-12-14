#pragma once

#include "core/defines.hpp"
#include "graphics/shader.hpp"
#include "graphics/textures.hpp"

namespace Noether {
    class Material {
        public:
            virtual void Apply() = 0;

        protected:
            Material(const std::shared_ptr<Shader>& shader) : m_Shader(shader) {}
            virtual ~Material() = default;

            std::shared_ptr<Shader> m_Shader;
    };

    // TODO: Look at pulling material types out into some material property block kind of thing

    class MaterialLit : public Material {
        public:
            static std::shared_ptr<MaterialLit> Create(const std::shared_ptr<Shader>& shader);
            MaterialLit(const std::shared_ptr<Shader>& shader);
            ~MaterialLit();

            void Apply() override;

            Vec4 AmbientColor;
            Vec4 DiffuseColor;
            Vec4 SpecularColor;
            std::shared_ptr<Texture2D> DiffuseMap;
            std::shared_ptr<Texture2D> SpecularMap;
            std::shared_ptr<Texture2D> NormalMap;
    };

    class MaterialUnlit : public Material {
        public:
            static std::shared_ptr<MaterialUnlit> Create(const std::shared_ptr<Shader>& shader);
            MaterialUnlit(const std::shared_ptr<Shader>& shader);
            ~MaterialUnlit();

            void Apply() override;

            Vec4 Color;
            std::shared_ptr<Texture2D> ColorMap;
    };
};