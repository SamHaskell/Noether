#include "graphics/shapes.hpp"

namespace Noether {
        std::shared_ptr<Mesh> Shapes::CreateSphere(f32 radius, u32 sectors, u32 stacks) {
            std::vector<Vertex> vertices = {};
            std::vector<Index> indices = {};

            Vertex vert;

            f32 sectorStep = 2.0f * PI / ((f32)sectors);
            f32 stackStep = PI / ((f32)stacks);
            f32 invRadius = 1.0f / radius;

            float phi, theta;   

            for (i32 i = 0; i <= stacks; i++) {
                phi = - (PI / 2.0f) + (i * stackStep);
                float rho = radius * cosf(phi);
                vert.Position.y = radius * sinf(phi);

                for (i32 j = 0; j <= sectors; j++) {
                    theta = j * sectorStep;

                    vert.Position.x = rho * cosf(theta);
                    vert.Position.z = rho * sinf(theta);

                    vert.Normal.x = vert.Position.x * invRadius;
                    vert.Normal.y = vert.Position.y * invRadius;
                    vert.Normal.z = vert.Position.z * invRadius;

                    vert.TexCoord.x = 1.0f - (f32)j / (f32)sectors;
                    vert.TexCoord.y = (f32)i / (f32)stacks;

                    vertices.push_back(vert);
                }
            }

            i32 k1, k2;

            for (u32 i = 0; i < stacks; i++) {
                k1 = i * (sectors + 1);
                k2 = k1 + sectors + 1;

                for (u32 j = 0; j < sectors; j++, k1++, k2++) {
                    if (i != 0) {
                        indices.push_back(k1);
                        indices.push_back(k2);
                        indices.push_back(k1 + 1);
                    }

                    if (i != (stacks - 1)) {
                        indices.push_back(k1 + 1);
                        indices.push_back(k2);
                        indices.push_back(k2 + 1);
                    }
                }
            }

            return Mesh::Create(vertices, indices, Matrix4::Identity());
        }

        std::shared_ptr<Mesh> Shapes::CreateCube(f32 side) {
            std::vector<Vertex> vertices = 
            {
                // front-side

                {   // left-bottom-front
                    .Position = {-0.5f*side, -0.5f*side, +0.5f*side},
                    .Normal = {-0.0f, -0.0f, +1.0f},
                    .TexCoord = {+0.0f, +0.0f}
                },
                {   // right-bottom-front
                    .Position = {+0.5f*side, -0.5f*side, +0.5f*side},
                    .Normal = {-0.0f, -0.0f, +1.0f},
                    .TexCoord = {+1.0f, +0.0f}
                },
                {   // right-top-front
                    .Position = {+0.5f*side, +0.5f*side, +0.5f*side},
                    .Normal = {-0.0f, -0.0f, +1.0f},
                    .TexCoord = {+1.0f, +1.0f}
                },
                {   // left-top-front
                    .Position = {-0.5f*side, +0.5f*side, +0.5f*side},
                    .Normal = {-0.0f, -0.0f, +1.0f},
                    .TexCoord = {+0.0f, +1.0f}
                },

                // right-side

                {   // right-bottom-front
                    .Position = {+0.5f*side, -0.5f*side, +0.5f*side},
                    .Normal = {+1.0f, +0.0f, +0.0f},
                    .TexCoord = {+0.0f, +0.0f}
                },
                {   // right-bottom-back
                    .Position = {+0.5f*side, -0.5f*side, -0.5f*side},
                    .Normal = {+1.0f, +0.0f, +0.0f},
                    .TexCoord = {+1.0f, +0.0f}
                },
                {   // right-top-back
                    .Position = {+0.5f*side, +0.5f*side, -0.5f*side},
                    .Normal = {+1.0f, +0.0f, +0.0f},
                    .TexCoord = {+1.0f, +1.0f}
                },
                {   // right-top-front
                    .Position = {+0.5f*side, +0.5f*side, +0.5f*side},
                    .Normal = {+1.0f, +0.0f, +0.0f},
                    .TexCoord = {+0.0f, +1.0f}
                },

                // left-side

                {
                    // left-bottom-back
                    .Position = {-0.5f*side, -0.5f*side, -0.5f*side},
                    .Normal = {-1.0f, +0.0f, +0.0f},
                    .TexCoord = {+0.0f, +0.0f}
                },
                {
                    // left-bottom-front
                    .Position = {-0.5f*side, -0.5f*side, +0.5f*side},
                    .Normal = {-1.0f, +0.0f, +0.0f},
                    .TexCoord = {+1.0f, +0.0f}
                },
                {
                    // left-top-front
                    .Position = {-0.5f*side, +0.5f*side, +0.5f*side},
                    .Normal = {-1.0f, +0.0f, +0.0f},
                    .TexCoord = {+1.0f, +1.0f}
                },
                {
                    // left-top-back
                    .Position = {-0.5f*side, +0.5f*side, -0.5f*side},
                    .Normal = {-1.0f, +0.0f, +0.0f},
                    .TexCoord = {+0.0f, +1.0f}
                },

                // back-side

                {
                    // right-bottom-back
                    .Position = {+0.5f*side, -0.5f*side, -0.5f*side},
                    .Normal = {+0.0f, +0.0f, +1.0f},
                    .TexCoord = {+0.0f, +0.0f}
                },
                {
                    // left-bottom-back
                    .Position = {-0.5f*side, -0.5f*side, -0.5f*side},
                    .Normal = {+0.0f, +0.0f, +1.0f},
                    .TexCoord = {+1.0f, +0.0f}
                },
                {
                    // left-top-back
                    .Position = {-0.5f*side, +0.5f*side, -0.5f*side},
                    .Normal = {+0.0f, +0.0f, +1.0f},
                    .TexCoord = {+1.0f, +1.0f}
                },
                {
                    // right-top-back
                    .Position = {+0.5f*side, +0.5f*side, -0.5f*side},
                    .Normal = {+0.0f, +0.0f, +1.0f},
                    .TexCoord = {+0.0f, +1.0f}
                },

                // top-side

                {
                    // left-top-front
                    .Position = {-0.5f*side, +0.5f*side, +0.5f*side},
                    .Normal = {+0.0f, +1.0f, +0.0f},
                    .TexCoord = {+0.0f, +0.0f}
                },
                {
                    // right-top-front
                    .Position = {+0.5f*side, +0.5f*side, +0.5f*side},
                    .Normal = {+0.0f, +1.0f, +0.0f},
                    .TexCoord = {+1.0f, +0.0f}
                },
                {
                    // right-top-back
                    .Position = {+0.5f*side, +0.5f*side, -0.5f*side},
                    .Normal = {+0.0f, +1.0f, +0.0f},
                    .TexCoord = {+1.0f, +1.0f}
                },
                {
                    // left-top-back
                    .Position = {-0.5f*side, +0.5f*side, -0.5f*side},
                    .Normal = {+0.0f, +1.0f, +0.0f},
                    .TexCoord = {+0.0f, +1.0f}
                },

                // bottom-side

                {
                    // left-bottom-back
                    .Position = {-0.5f*side, -0.5f*side, -0.5f*side},
                    .Normal = {+0.0f, -1.0f, +0.0f},
                    .TexCoord = {+0.0f, +0.0f}
                },
                {
                    // right-bottom-back
                    .Position = {+0.5f*side, -0.5f*side, -0.5f*side},
                    .Normal = {+0.0f, -1.0f, +0.0f},
                    .TexCoord = {+1.0f, +0.0f}
                },
                {
                    // right-bottom-front
                    .Position = {+0.5f*side, -0.5f*side, +0.5f*side},
                    .Normal = {+0.0f, -1.0f, +0.0f},
                    .TexCoord = {+1.0f, +1.0f}
                },
                {
                    // left-bottom-front
                    .Position = {-0.5f*side, -0.5f*side, +0.5f*side},
                    .Normal = {+0.0f, -1.0f, +0.0f},
                    .TexCoord = {+0.0f, +1.0f}
                }
            };

            std::vector<Index> indices = {
                0, 1, 2, 2, 3, 0,
                4, 5, 6, 6, 7, 4,
                8, 9, 10, 10, 11, 8,
                12, 13, 14, 14, 15, 12,
                16, 17, 18, 18, 19, 16,
                20, 21, 22, 22, 23, 20
            };

            return Mesh::Create(vertices, indices, Matrix4::Identity());
        }
};