#shader vertex
#version 410 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_ViewToProjectionMatrix;

void main() {
    gl_Position = u_ViewToProjectionMatrix * vec4(a_Position, 0.0, 1.0);
    v_TexCoord = a_TexCoord;
}

#shader fragment
#version 410 core

in vec2 v_TexCoord;

out vec4 f_Color;

uniform sampler2D u_GlyphTex;
uniform vec3 u_TextColor;

void main() {
    vec4 glyphSample = vec4(1.0, 1.0, 1.0, texture(u_GlyphTex, v_TexCoord).r);
    f_Color = vec4(u_TextColor, 1.0) * glyphSample;
}