#version 400

layout(location = 0) in vec3 vertexPosition;

void main()
{
	gl_Position = vec4(vertexPosition, 1.0);
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

uniform mat4 u_shR;
uniform mat4 u_shG;
uniform mat4 u_shB;

vec2 GetUv()
{
	return gl_FragCoord.xy/vec2(u_width, u_height);
}

// Include ssao
$data/ssao.fx$

vec4 radiance(vec3 normal)
{
	vec4 final;
	vec4 castedNormal = normalize(vec4(normal, 1));

	final.r = clamp(dot(castedNormal, u_shR * castedNormal),0.0,1.0);
	final.g = clamp(dot(castedNormal, u_shG* castedNormal),0.0,1.0);
	final.b = clamp(dot(castedNormal, u_shB * castedNormal),0.0,1.0);
	final.a = 1;

	return final;
}

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
	if(texture(u_gViewPosDepth,uv).w == 420)
		color = texture(u_gColor, uv) * (diffuse + vec4(0.2)) + texture(u_gLightTexture, uv);
	else if(texture(u_gViewPosDepth,uv).w == 69)
		color = texture(u_gColor, uv); 
	else
		color = texture(u_gColor, uv) * (diffuse +  radiance(normal)) + texture(u_gLightTexture, uv) * AmbientOcclusion(uv);

}
