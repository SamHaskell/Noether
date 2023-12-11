#shader vertex
#version 410 core

uniform mat4 u_ModelToWorldMatrix;
uniform mat4 u_WorldToProjectionMatrix;
uniform mat4 u_WorldToDirectionalLightMatrix;

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

out vec3 v_PositionWS;
out vec3 v_NormalWS;
out vec2 v_TexCoord;
out vec4 v_PositionDirectionalLightSpace;

void main() {
    // TODO: Currently non-uniform scaling is not supported. We need to pass a matrix for transforming normals seperately ...

    v_PositionWS = vec3(u_ModelToWorldMatrix * vec4(a_Position, 1.0f));
    v_NormalWS = vec3(u_ModelToWorldMatrix * vec4(a_Normal, 0.0f));
    v_TexCoord = a_TexCoord;
    v_PositionDirectionalLightSpace = u_WorldToDirectionalLightMatrix * vec4(v_PositionWS, 1.0);
    gl_Position = u_WorldToProjectionMatrix * u_ModelToWorldMatrix * vec4(a_Position, 1.0);
}

#shader fragment
#version 410 core

struct Material {
    vec4 AmbientColor;
    vec4 DiffuseColor;
    vec4 SpecularColor;
    sampler2D DiffuseMap;
    sampler2D SpecularMap;
};

struct DirectionalLight {
    vec4 AmbientColor;
    float AmbientIntensity;
    vec4 Color;
    float Intensity;
    vec3 DirectionWS;
};

struct PointLight {
    vec4 AmbientColor;
    float AmbientIntensity;
    vec4 Color;
    vec3 PositionWS;
    float ConstantAttenuation;
    float LinearAttenuation;
    float QuadraticAttenuation;
};

uniform Material u_MaterialLit;

uniform DirectionalLight u_DirectionalLight;
uniform PointLight u_PointLight;

uniform vec3 u_EyePositionWS;

uniform sampler2D u_ShadowMap;

in vec3 v_PositionWS;
in vec3 v_NormalWS;
in vec2 v_TexCoord;
in vec4 v_PositionDirectionalLightSpace;

out vec4 f_Color;

vec4 calculate_directional_lighting(DirectionalLight light, vec3 normal, vec3 viewDir, vec4 positionLightSpace);
vec4 calculate_point_lighting(PointLight light, vec3 normal, vec3 viewDir);
float calculate_shadow_factor(vec4 positionLightSpace);

void main() {
    vec3 normal = normalize(v_NormalWS);
    vec3 viewDir = normalize(u_EyePositionWS - v_PositionWS);

    vec4 directionalLighting = calculate_directional_lighting(u_DirectionalLight, normal, viewDir, v_PositionDirectionalLightSpace);
    vec4 pointLighting = calculate_point_lighting(u_PointLight, normal, viewDir);

    f_Color = directionalLighting + pointLighting;
}

vec4 calculate_directional_lighting(DirectionalLight light, vec3 normal, vec3 viewDir, vec4 positionLightSpace) {
    vec4 diffuseMap = texture(u_MaterialLit.DiffuseMap, v_TexCoord);
    vec4 specularMap = texture(u_MaterialLit.SpecularMap, v_TexCoord);

    vec3 lightDir = - normalize(light.DirectionWS);

    // Ambient
    vec4 ambientLight = u_MaterialLit.DiffuseColor * diffuseMap * light.AmbientColor * light.AmbientIntensity;

    // Diffuse
    float diffuseStrength = max(dot(normalize(normal), lightDir), 0.0);
    vec4 diffuseLight = diffuseStrength * u_MaterialLit.DiffuseColor * diffuseMap * light.Color * light.Intensity;

    // Specular
    vec3 reflectedLightVecWS = reflect(-lightDir, normal);
    float specularity = clamp(dot(reflectedLightVecWS, viewDir), 0.0f, 1.0f);
    float specularStrength = pow(specularity, 64.0f);
    vec4 specularLight = specularStrength * u_MaterialLit.SpecularColor * specularMap * light.Color * light.Intensity;

    float shadowFactor = calculate_shadow_factor(positionLightSpace);

    return (ambientLight + (1.0f - shadowFactor) * (diffuseLight + specularLight));
}

vec4 calculate_point_lighting(PointLight light, vec3 normal, vec3 viewDir) {
    vec4 diffuseMap = texture(u_MaterialLit.DiffuseMap, v_TexCoord);
    vec4 specularMap = texture(u_MaterialLit.SpecularMap, v_TexCoord);

    vec3 lightVec = light.PositionWS - v_PositionWS;
    float lightDistSquare = dot(lightVec, lightVec);
    vec3 lightDir = normalize(lightVec);

    float attenuation = 1.0f / (light.ConstantAttenuation + light.LinearAttenuation * sqrt(lightDistSquare) + light.QuadraticAttenuation * lightDistSquare);

    // Ambient
    vec4 ambientLight = u_MaterialLit.AmbientColor * light.AmbientColor * light.AmbientIntensity * diffuseMap;

    // Diffuse
    vec4 diffuseLight = u_MaterialLit.DiffuseColor * light.Color * diffuseMap * clamp(dot(lightDir, normal), 0.0f, 1.0f);

    // Specular
    vec3 reflectedLightVecWS = reflect(-lightDir, normal);
    float specularity = clamp(dot(reflectedLightVecWS, viewDir), 0.0f, 1.0f);
    float specularStrength = pow(specularity, 64.0f);
    vec4 specularLight = u_MaterialLit.SpecularColor * light.Color * specularMap * specularStrength;

    // Sum contributions
    return (specularLight + diffuseLight + ambientLight) * attenuation;
}

float calculate_shadow_factor(vec4 positionLightSpace) {
    float shadow;

    vec3 projCoords = positionLightSpace.xyz / positionLightSpace.w;
    projCoords = (projCoords * 0.5) + 0.5;
    float depthTest = texture(u_ShadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    float bias = 0.005;

    shadow = currentDepth - bias > depthTest ? 1.0 : 0.0;

    if(projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}