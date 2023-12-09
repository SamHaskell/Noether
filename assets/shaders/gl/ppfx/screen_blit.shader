#shader vertex
#version 410 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main() {
    v_TexCoord = a_TexCoord;
    gl_Position = vec4(a_Position, 0.0, 1.0);
}

#shader fragment
#version 410 core

in vec2 v_TexCoord;

out vec4 f_Color;

uniform sampler2D u_BlitTexture;

void main() {
    f_Color = texture(u_BlitTexture, v_TexCoord);
}