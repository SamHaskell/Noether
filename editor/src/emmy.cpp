#include "emmy.hpp"
#include "imgui.h"

namespace Noether {
    void Editor::Initialise() {
        GetGraphicsDevice()->SetVSync(false);
        auto window = GetMainWindow();
        m_MultisampledFramebuffer = FrameBuffer::Create(window->GetBackbufferWidth(), window->GetBackbufferHeight(), 4);
        m_ResolvedFramebuffer = FrameBuffer::Create(window->GetBackbufferWidth(), window->GetBackbufferHeight(), 0);
        m_ShadowMap = DepthBuffer::Create(2048, 2048);

        // m_TestMesh = Mesh::Load("assets/models/crab.obj");
        m_TestMesh = Shapes::CreateSphere(3.0f, 256, 128);
        m_CubeMesh = Shapes::CreateCube();
        
        m_TestAlbedo = Texture2D::Create("assets/textures/earth_day.jpg");
        m_WhiteTexture = Texture2D::Create("assets/debug/debug_texture_white.png");

        m_LitShader = Shader::Create("assets/shaders/gl/3d/basic_lit.shader");

        m_DepthPrepass = Shader::Create("assets/shaders/gl/3d/prepass_depth.shader");

        m_TestMaterial = MaterialLit::Create(m_LitShader);

        m_TestMaterial->AmbientColor = {1.0f, 1.0f, 1.0f, 1.0f};
        m_TestMaterial->DiffuseColor = {1.0f, 1.0f, 1.0f, 1.0f};
        m_TestMaterial->SpecularColor = {1.0f, 1.0f, 1.0f, 1.0f};
        m_TestMaterial->DiffuseMap = m_TestAlbedo;
        m_TestMaterial->SpecularMap = m_WhiteTexture;

        m_GroundMaterial = MaterialLit::Create(m_LitShader);

        m_GroundMaterial->AmbientColor = {1.0f, 1.0f, 1.0f, 1.0f};
        m_GroundMaterial->DiffuseColor = {1.0f, 1.0f, 1.0f, 1.0f};
        m_GroundMaterial->SpecularColor = {1.0f, 1.0f, 1.0f, 1.0f};
        m_GroundMaterial->DiffuseMap = m_WhiteTexture;
        m_GroundMaterial->SpecularMap = m_WhiteTexture;

        m_UnlitShader = Shader::Create("assets/shaders/gl/3d/basic_unlit.shader");
        m_UnlitMaterial = MaterialUnlit::Create(m_UnlitShader);

        m_UnlitMaterial->Color = {1.0f, 1.0f, 1.0f, 1.0f};
        m_UnlitMaterial->ColorMap = m_WhiteTexture;

        m_BlitShader = Shader::Create("assets/shaders/gl/ppfx/screen_blit.shader");
        m_DepthBlitShader = Shader::Create("assets/shaders/gl/ppfx/depth_blit.shader");

        m_SkyShader = Shader::Create("assets/shaders/gl/sky/test_sky.shader");

        CubeMapData cubeMapData = {
            .Paths = {
                    "assets/cubemaps/blue_sunset/blue_sunset_+X.png",
                    "assets/cubemaps/blue_sunset/blue_sunset_-X.png",
                    "assets/cubemaps/blue_sunset/blue_sunset_+Y.png",
                    "assets/cubemaps/blue_sunset/blue_sunset_-Y.png",
                    "assets/cubemaps/blue_sunset/blue_sunset_+Z.png",
                    "assets/cubemaps/blue_sunset/blue_sunset_-Z.png"
            }
        };

        m_CubeMap = TextureCube::Create(cubeMapData);

        f32 quadVertices[] = {
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 1.0f
        };

        Index quadIndices[] = {
            0, 1, 2, 2, 3, 0
        };

        BufferLayout quadLayout = {
            {BufferElementType::Float2, "a_Position"},
            {BufferElementType::Float2, "a_TexCoord"}
        };

        m_QuadVA = VertexArray::Create(
            VertexBuffer::Create(quadVertices, 4 * 4 * sizeof(f32)),
            IndexBuffer::Create(quadIndices, 6),
            quadLayout
        );

        f32 cubeMapVertices[] = {
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
        };

        Index cubeMapIndices[] = {
            0, 1, 2, 3, 4, 5,
            6, 7, 8, 9, 10, 11,
            12, 13, 14, 15, 16, 17,
            18, 19, 20, 21, 22, 23,
            24, 25, 26, 27, 28, 29,
            30, 31, 32, 33, 34, 35
        };

        BufferLayout cubeMapLayout = {
            {BufferElementType::Float3, "a_Position"}
        };

        m_CubeMapVA = VertexArray::Create(
            VertexBuffer::Create(cubeMapVertices, 36 * 3 * sizeof(f32)),
            IndexBuffer::Create(cubeMapIndices, 36),
            cubeMapLayout
        );

        m_PointLight = {
            .AmbientColor = {1.0f, 1.0f, 1.0f, 1.0f},
            .AmbientIntensity = 0.2f,
            .Color = {1.0f, 1.0f, 1.0f, 1.0f},
            .Position = {0.0f, 3.0f, 0.0f},
        };

        m_GroundTransform = {
            .Position = {0.0f, -3.0f, 0.0f},
            .Scale = {10000.0f, 1.0f, 10000.0f}
        };

        m_CameraTransform = {
            .Position = {0.0f, 3.0f, 5.0f},
            .Rotation = {-30.0f, 0.0f, 0.0f}
        };

        m_TestTransform = {
            .Position = {0.0f, 2.0f, 0.0f}
        };
    }

    void Editor::Shutdown() {

    }

    void Editor::Update(f64 dt) {
        m_DebugData.FrameTime = dt;
        m_UnlitMaterial->Color = m_PointLight.Color;

        if (m_CameraFocused) {
            Vec3 moveInput = {0.0f, 0.0f, 0.0f};
            {
                if (Input::IsKeyPressed(KeyCode::W)) {
                    moveInput.z -= 1.0f * dt;
                }

                if (Input::IsKeyPressed(KeyCode::S)) {
                    moveInput.z += 1.0f * dt;
                }

                if (Input::IsKeyPressed(KeyCode::A)) {
                    moveInput.x -= 1.0f * dt;
                }

                if (Input::IsKeyPressed(KeyCode::D)) {
                    moveInput.x += 1.0f * dt;
                }

                if (Input::IsKeyPressed(KeyCode::Q)) {
                    moveInput.y -= 1.0f * dt;
                }

                if (Input::IsKeyPressed(KeyCode::E)) {
                    moveInput.y += 1.0f * dt;
                }
            }

            m_CameraTransform.Position += m_CameraTransform.TransformDirection(moveInput * 3.0f);

            Vec2 mousePos = Input::GetMousePosition();
            Input::RecenterMousePosition();

            f32 pitchDelta = (f32)(GetMainWindow()->GetScreenHeight()/2 - mousePos.y) * (f32)dt * 30.0f; 
            f32 yawDelta = (f32)(GetMainWindow()->GetScreenWidth()/2 - mousePos.x) * (f32)dt * 30.0f; 

            m_CameraTransform.Rotation.x = Maths::Clamp(m_CameraTransform.Rotation.x + pitchDelta, -89.9f, 89.9f);
            m_CameraTransform.Rotation.y = m_CameraTransform.Rotation.y + yawDelta;
        };
    }

    void Editor::Render() {

        // Shadow-mapping prepass for the directional light

        m_ShadowMap->Bind();
        GetGraphicsDevice()->SetViewport(m_ShadowMap->GetWidth(), m_ShadowMap->GetHeight());

        GetGraphicsDevice()->Clear(ClearFlags(ClearFlagBits::Depth));

        // Set up virtual camera (orthographic here for a directional light)

        Vec3 lightDir = m_DirectionalLight.Direction;
        Mat4 lightView = Matrix4::ViewLookDir(m_CameraTransform.Position - (lightDir * 10.0f), lightDir);
        Mat4 lightProj = Matrix4::Orthographic(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 1000.0f);

        m_DepthPrepass->Bind();
        m_DepthPrepass->SetUniformMat4("u_WorldToProjectionMatrix", lightProj * lightView);

        {
            {
                Mat4 model = m_TestTransform.LocalTransform();
                m_DepthPrepass->SetUniformMat4("u_ModelToWorldMatrix", model);
                GetGraphicsDevice()->DrawVertexArray(m_TestMesh->GetVertexArray());
            }

            {                    
                Mat4 model = m_GroundTransform.LocalTransform();
                m_DepthPrepass->SetUniformMat4("u_ModelToWorldMatrix", model);
                GetGraphicsDevice()->DrawVertexArray(m_CubeMesh->GetVertexArray());
            }
            
            {
                Mat4 model = Matrix4::Translation(m_PointLight.Position) * Matrix4::Scale(0.1, 0.1, 0.1);
                m_DepthPrepass->SetUniformMat4("u_ModelToWorldMatrix", model);
                GetGraphicsDevice()->DrawVertexArray(m_CubeMesh->GetVertexArray());                    
            }
        }

        GetGraphicsDevice()->SetViewport(GetMainWindow()->GetBackbufferWidth(), GetMainWindow()->GetBackbufferHeight());

        // Bind the framebuffer

        m_MultisampledFramebuffer->Bind();

        GetGraphicsDevice()->Clear();

        // Set up camera.

        Vec3 lookDir = Vector3::DirectionFromEuler(m_CameraTransform.Rotation);
        Mat4 view = Matrix4::ViewLookDir(m_CameraTransform.Position, lookDir);

        f32 aspect = (f32)GetMainWindow()->GetBackbufferWidth() / (f32)GetMainWindow()->GetBackbufferHeight();
        Mat4 proj = Matrix4::Perspective(60.0f, aspect, 0.1f, 1000.0f);

        // Skybox!

        m_SkyShader->Bind();
        m_SkyShader->SetUniformMat4("u_WorldToViewMatrix", view);
        m_SkyShader->SetUniformMat4("u_ViewToProjectionMatrix", proj);
        m_CubeMap->Bind();

        GetGraphicsDevice()->SetDepthTesting(false);
        GetGraphicsDevice()->DrawVertexArray(m_CubeMapVA);
        GetGraphicsDevice()->SetDepthTesting(true);

        { // For each shader.
            m_LitShader->Bind();
            m_LitShader->SetUniformMat4("u_WorldToProjectionMatrix", proj * view);
            m_LitShader->SetUniformFloat3("u_EyePositionWS", m_CameraTransform.Position);

            // Apply point light uniforms.

            m_LitShader->SetUniformFloat4("u_PointLight.AmbientColor", m_PointLight.AmbientColor);
            m_LitShader->SetUniformFloat("u_PointLight.AmbientIntensity", m_PointLight.AmbientIntensity);
            m_LitShader->SetUniformFloat4("u_PointLight.Color", m_PointLight.Color);
            m_LitShader->SetUniformFloat3("u_PointLight.PositionWS", m_PointLight.Position);

            m_LitShader->SetUniformFloat("u_PointLight.ConstantAttenuation", m_PointLight.ConstantAttenuation);
            m_LitShader->SetUniformFloat("u_PointLight.LinearAttenuation", m_PointLight.LinearAttenuation);
            m_LitShader->SetUniformFloat("u_PointLight.QuadraticAttenuation", m_PointLight.QuadraticAttenuation);

            // Apply directional light uniforms.

            m_LitShader->SetUniformFloat4("u_DirectionalLight.AmbientColor", m_DirectionalLight.AmbientColor);
            m_LitShader->SetUniformFloat("u_DirectionalLight.AmbientIntensity", m_DirectionalLight.AmbientIntensity);
            m_LitShader->SetUniformFloat4("u_DirectionalLight.Color", m_DirectionalLight.Color);
            m_LitShader->SetUniformFloat("u_DirectionalLight.Intensity", m_DirectionalLight.Intensity);
            m_LitShader->SetUniformFloat3("u_DirectionalLight.DirectionWS", m_DirectionalLight.Direction);
            
            { // For each material that uses that shader.
                m_TestMaterial->Apply();

                { // For each model that uses that material.
                    Mat4 model = m_TestTransform.LocalTransform();
                    m_LitShader->SetUniformMat4("u_ModelToWorldMatrix", model);
                    GetGraphicsDevice()->DrawVertexArray(m_TestMesh->GetVertexArray());
                }

                m_GroundMaterial->Apply();

                {
                    Mat4 model = m_GroundTransform.LocalTransform();
                    m_LitShader->SetUniformMat4("u_ModelToWorldMatrix", model);
                    GetGraphicsDevice()->DrawVertexArray(m_CubeMesh->GetVertexArray());
                }
            }

            m_UnlitShader->Bind();
            m_UnlitShader->SetUniformMat4("u_WorldToProjectionMatrix", proj * view);

            {
                m_UnlitMaterial->Apply();

                {
                    Mat4 model = Matrix4::Translation(m_PointLight.Position) * Matrix4::Scale(0.1, 0.1, 0.1);
                    m_UnlitShader->SetUniformMat4("u_ModelToWorldMatrix", model);
                    GetGraphicsDevice()->DrawVertexArray(m_CubeMesh->GetVertexArray());
                }
            }
        }

        // Blit the framebuffer onto the screen

        IRect2D screenRect = {
            0, 0, GetMainWindow()->GetBackbufferWidth(), GetMainWindow()->GetBackbufferHeight()
        };

        GetGraphicsDevice()->Blit(m_MultisampledFramebuffer, m_ResolvedFramebuffer, screenRect, screenRect);

        m_MultisampledFramebuffer->Unbind();
        m_ResolvedFramebuffer->Unbind();

        m_BlitShader->Bind();
        m_ResolvedFramebuffer->GetColorAttachment()->Bind();
        GetGraphicsDevice()->DrawVertexArray(m_QuadVA);
    }

    void Editor::DrawGUI() {
        ImGui::BeginMainMenuBar();
        {
            ImGui::Text("Testing!");
        }
        ImGui::EndMainMenuBar();

        ImGui::Begin("Debug Data");
        {
            ImGui::Text("Frame Time (ms): %-8.3f", m_DebugData.FrameTime * 1000.0);
        }
        ImGui::End();

        ImGui::Begin("Light Settings");
        {
            ImGui::Text("Directional Light");
            ImGui::PushID(__LINE__);
            {
                ImGui::ColorEdit4("Ambient Color", &m_DirectionalLight.AmbientColor.x);
                ImGui::DragFloat("Ambient Intensity", &m_DirectionalLight.AmbientIntensity, 0.01f, 0.0f, 5.0f);
                ImGui::ColorEdit4("Color", &m_DirectionalLight.Color.x);
                ImGui::DragFloat("Intensity", &m_DirectionalLight.Intensity, 0.01f, 0.0f, 1.0f);
                ImGui::DragFloat3("Direction", &m_DirectionalLight.Direction.x, 0.01f);
            }   
            ImGui::PopID();

            ImGui::Text("Point Light");
            ImGui::PushID(__LINE__);
            {
                ImGui::ColorEdit4("Ambient Color", &m_PointLight.AmbientColor.x);
                ImGui::DragFloat("Ambient Intensity", &m_PointLight.AmbientIntensity, 0.01f, 0.0f, 5.0f);
                ImGui::ColorEdit4("Color", &m_PointLight.Color.x);
                ImGui::DragFloat3("Position", &m_PointLight.Position.x, 0.01f);

                ImGui::DragFloat("Constant Attenuation", &m_PointLight.ConstantAttenuation, 0.01f, 0.0f, 5.0f);
                ImGui::DragFloat("Linear Attenuation", &m_PointLight.LinearAttenuation, 0.01f, 0.0f, 5.0f);
                ImGui::DragFloat("Quadratic Attenuation", &m_PointLight.QuadraticAttenuation, 0.01f, 0.0f, 5.0f);
            }
            ImGui::PopID();
        }
        ImGui::End();

        ImGui::Begin("Model Transform");
        {
            ImGui::DragFloat3("Scale", &m_TestTransform.Scale.x, 0.01f);
            ImGui::DragFloat3("Position", &m_TestTransform.Position.x, 0.01f);
            ImGui::DragFloat3("Rotation", &m_TestTransform.Rotation.x, 0.36f);
        }
        ImGui::End();

        ImGui::Begin("Camera Transform");
        {
            ImGui::DragFloat3("Scale", &m_CameraTransform.Scale.x, 0.01f);
            ImGui::DragFloat3("Position", &m_CameraTransform.Position.x, 0.01f);
            ImGui::DragFloat3("Rotation", &m_CameraTransform.Rotation.x, 0.36f);
        }
        ImGui::End();
    }

    void Editor::OnEvent(Event& e) {
        switch (e.Type) {
            case Event::Type::WindowBackbufferSize:
            {
                m_MultisampledFramebuffer->Resize(e.WindowBackbufferSize.Width, e.WindowBackbufferSize.Height);
                m_ResolvedFramebuffer->Resize(e.WindowBackbufferSize.Width, e.WindowBackbufferSize.Height);
                break;
            }
            case Event::Type::Key:
            {
                switch (e.KeyPress.Key) {
                    case KeyCode::Esc:
                        if (e.KeyPress.IsDown) {
                            Input::SetCursorMode(CursorMode::Regular);
                            m_CameraFocused = false;
                        }
                        break;
                    case KeyCode::Space:
                        if (e.KeyPress.IsDown) {
                            Input::SetCursorMode(CursorMode::Disabled);
                            m_CameraFocused = true;
                        }
                    default:
                        break;
                }
            }
            default:
                break;
        }
    }
};