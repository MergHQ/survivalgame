#version 400

layout(location = 0) in vec3 vertexPosition;

uniform mat4 u_modelMat;
uniform mat4 u_viewMat;
uniform mat4 u_projMat;

void main()
{
	vec4 viewPos = u_viewMat * u_modelMat * vec4(vertexPosition, 1.0);
	gl_Position = u_projMat*viewPos;
}

@

#version 400

out vec4 color;

uniform sampler2D u_gColor;
uniform sampler2D u_gNormal;
uniform sampler2D u_gPos;

uniform vec3 u_lightColor;
uniform vec3 u_lightPos;
uniform vec3 u_lightAtt;

uniform int u_width;
uniform int u_height;

vec2 GetUv()
{
	return gl_FragCoord.xy/vec2(u_width, u_height);
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
	float attenuation = 1.0;
	if(NdotL > 0.0)
		diffuse = vec4(u_lightColor*NdotL, 1);
	
	float distanceToLight = length(u_lightPos - position);
	attenuation /= (u_lightAtt.x * 0.1) + ((u_lightAtt.y* 0.1) * distanceToLight) + ((u_lightAtt.y * 0.1)* distanceToLight * distanceToLight);
	diffuse *= attenuation;

	color = texture(u_gColor, uv) * diffuse;
}