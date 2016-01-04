#version 400

layout(location = 0) in vec3 vertexPosition;

void main()
{
	gl_Position = vec4(vertexPosition, 1.0);
	float tanHalfFov = tan((45/2)*(3.14/180));
	float aspectRatio = 1280.0/720.0;
}

@

#version 400

out vec4 color;

uniform sampler2D u_gColor;
uniform sampler2D u_gNormal;
uniform sampler2D u_gPos;
uniform sampler2D u_gDepth;
uniform sampler2D u_gViewPosDepth;
uniform sampler2D u_gViewNormal;
uniform sampler2D u_gLightTexture;

uniform vec3 u_ssaoKernel[64];
uniform float u_ssaoRadius;
uniform mat4 u_projMat;
uniform vec3 u_cameraPos;
uniform sampler2D u_noiseTexture;

uniform vec3 u_lightColor;
uniform vec3 u_lightPos;

uniform int u_width;
uniform int u_height;

vec2 GetUv()
{
	return gl_FragCoord.xy/vec2(1920, 1080);
}

// Include ssao
$data/ssao.fx$

void main()
{
	vec2 uv = GetUv();
	vec3 normal = texture(u_gNormal, uv).xyz;
	vec3 position = texture(u_gPos, uv).xyz;

	vec3 lightPos = u_lightPos;
	vec3 lightDir = normalize(lightPos - position);
	float NdotL = dot(normalize(normal), lightDir);
	vec4 diffuse = vec4(0);
	if(NdotL > 0.0)
		diffuse = vec4(u_lightColor*NdotL, 1);
	if(texture(u_gViewPosDepth,uv).w != 420)
		color = texture(u_gColor, uv) * (diffuse + vec4(0.2)) + texture(u_gLightTexture, uv) * AmbientOcclusion(uv);
	else
		color = texture(u_gColor, uv) * (diffuse + vec4(0.2)) + texture(u_gLightTexture, uv);
}
