#version 400

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 u_modelMat;
uniform mat4 u_viewMat;
uniform mat4 u_projMat;
uniform mat4 u_2world;

out vec3 v_normal;
out vec3 v_pos;

out vec3 v_fragPos;
out vec3 v_fragNormal;

void main()
{
	vec4 viewPos = u_viewMat * u_modelMat * vec4(vertexPosition, 1.0);
	v_fragPos = viewPos.xyz;
	v_fragNormal = transpose(inverse(mat3(u_viewMat * u_modelMat))) * normal; 
	v_normal = (u_2world * vec4(normal, 0.0)).xyz;
	v_pos = (u_2world * vec4(vertexPosition, 1.0)).xyz;
	gl_Position = u_projMat*viewPos;
}

@

#version 400
layout(location = 0) out vec4 gColor;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec3 gPos;
layout(location = 3) out vec4 gDepthPos;
layout(location = 4) out vec4 gViewNormal;


in vec3 v_normal;
in vec3 v_pos;

in vec3 v_fragPos;
in vec3 v_fragNormal;

const float NEAR = 0.1f;
const float FAR = 1000.0f;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));		
}

void main()
{
	gNormal = v_normal;
	gPos = v_pos;
	gDepthPos.xyz = v_fragPos;
	gDepthPos.w = 420; // magical number
	gViewNormal.xyz = normalize(v_normal);
	gViewNormal.w = 1.0;
	gColor = vec4(0.6,0.7,0.75,1);
}
