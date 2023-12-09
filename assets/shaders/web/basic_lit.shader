#shader vertex
#version 300 es

in vec3 a_Position;
in vec3 a_Normal;
in vec2 a_TexCoord;

out vec3 v_Normal;
out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection; 

void main() {
    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
    v_TexCoord = a_TexCoord;
    v_Normal = a_Normal;
}

#shader fragment
#version 300 es

precision mediump float

in vec3 v_Normal;
in vec2 v_TexCoord;

out vec4 f_Color;

void main() {
    f_Color = vec4(v_Normal, 1.0);
}