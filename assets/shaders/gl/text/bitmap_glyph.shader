#shader vertex
#version 410 core

layout(location = 0) in vec3 a_Position;

out vec3 v_TexCoord;

uniform mat4 u_ViewToProjectionMatrix;
uniform mat4 u_WorldToViewMatrix;

void main() {
    v_TexCoord = a_Position;
    gl_Position = u_ViewToProjectionMatrix * mat4(mat3(u_WorldToViewMatrix)) * vec4(a_Position, 1.0);
}

#shader fragment
#version 410 core

in vec3 v_TexCoord;

out vec4 f_Color;

uniform samplerCube u_CubeMap;

void main() {
    f_Color = texture(u_CubeMap, v_TexCoord);
}