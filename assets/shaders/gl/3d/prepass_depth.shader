#shader vertex
#version 410 core

uniform mat4 u_ModelToWorldMatrix;
uniform mat4 u_WorldToProjectionMatrix;

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

void main() {
    gl_Position = u_WorldToProjectionMatrix * u_ModelToWorldMatrix * vec4(a_Position, 1.0);
}

#shader fragment
#version 410 core

void main() {
    // gl_FragDepth = gl_FragCoord.z
}