#pragma once

#include "noether.hpp"

namespace Noether {
    class Editor : public App {
        public:
            Editor() = default;
            ~Editor() = default;

            void Initialise() override;
            void Shutdown() override;

            void Update(f64 dt) override;
            void Render() override;
            void DrawGUI() override;
            void OnEvent(Event& e) override;

        private:
            std::shared_ptr<FrameBuffer> m_MultisampledFramebuffer;
            std::shared_ptr<FrameBuffer> m_ResolvedFramebuffer;

            std::shared_ptr<DepthBuffer> m_ShadowMap;

            std::shared_ptr<Texture2D> m_WhiteTexture;
            std::shared_ptr<Texture2D> m_TestAlbedo;
            
            std::shared_ptr<Shader> m_LitShader;
            std::shared_ptr<Shader> m_UnlitShader;
            std::shared_ptr<Shader> m_BlitShader;
            std::shared_ptr<Shader> m_SkyShader;

            std::shared_ptr<MaterialLit> m_TestMaterial;
            std::shared_ptr<MaterialLit> m_GroundMaterial;
            std::shared_ptr<MaterialUnlit> m_UnlitMaterial;
            
            std::shared_ptr<Mesh> m_CubeMesh;
            std::shared_ptr<Mesh> m_TestMesh;

            std::shared_ptr<VertexArray> m_QuadVA;
            std::shared_ptr<VertexArray> m_CubeMapVA;

            std::shared_ptr<TextureCube> m_CubeMap;
            
            Transform m_TestTransform;
            Transform m_GroundTransform;
            Transform m_CameraTransform;

            PointLight m_PointLight;
            DirectionalLight m_DirectionalLight;

            struct DebugData {
                f64 FrameTime;
            } m_DebugData;
    };
};