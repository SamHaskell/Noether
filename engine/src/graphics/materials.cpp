#include "graphics/materials.hpp"

namespace Noether {
    std::shared_ptr<MaterialLit> MaterialLit::Create(const std::shared_ptr<Shader>& shader) {
        return std::make_shared<MaterialLit>(shader);
    }

    MaterialLit::MaterialLit(const std::shared_ptr<Shader>& shader) 
    : Material(shader)
    {

    }

    MaterialLit::~MaterialLit() {

    }
    
    void MaterialLit::Apply() {
        m_Shader->SetUniformFloat4("u_MaterialLit.AmbientColor", AmbientColor);
        m_Shader->SetUniformFloat4("u_MaterialLit.DiffuseColor", DiffuseColor);
        m_Shader->SetUniformFloat4("u_MaterialLit.SpecularColor", SpecularColor);

        DiffuseMap->Bind(0);
        m_Shader->SetUniformInt("u_MaterialLit.DiffuseMap", 0);

        SpecularMap->Bind(1);
        m_Shader->SetUniformInt("u_MaterialLit.SpecularMap", 1);

        NormalMap->Bind(2);
        m_Shader->SetUniformInt("u_MaterialLit.NormalMap", 2);
    }

    std::shared_ptr<MaterialUnlit> MaterialUnlit::Create(const std::shared_ptr<Shader>& shader) {
        return std::make_shared<MaterialUnlit>(shader);
    }

    MaterialUnlit::MaterialUnlit(const std::shared_ptr<Shader>& shader) 
    : Material(shader)
    {

    }

    MaterialUnlit::~MaterialUnlit() {

    }
    
    void MaterialUnlit::Apply() {
        m_Shader->SetUniformFloat4("u_MaterialUnlit.Color", Color);

        ColorMap->Bind(0);
        m_Shader->SetUniformInt("u_MaterialLit.ColorMap", 0);
    }
}