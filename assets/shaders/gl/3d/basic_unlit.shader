#shader vertex
#version 410 core

uniform mat4 u_ModelToWorldMatrix;
uniform mat4 u_WorldToProjectionMatrix;

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main() {
    v_TexCoord = a_TexCoord;
    gl_Position = u_WorldToProjectionMatrix * u_ModelToWorldMatrix * vec4(a_Position, 1.0);
}

#shader fragment
#version 410 core

struct Material {
    vec4 Color;
    sampler2D ColorMap;
};

uniform Material u_MaterialUnlit;

in vec2 v_TexCoord;

out vec4 f_Color;

void main() {
    f_Color = u_MaterialUnlit.Color * texture(u_MaterialUnlit.ColorMap, v_TexCoord);
}