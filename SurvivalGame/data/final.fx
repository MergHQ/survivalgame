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

uniform int u_width;
uniform int u_height;

vec2 GetUv()
{
	return gl_FragCoord.xy/vec2(u_width, u_height);
}

float linearizeDepth(vec2 coord)
{
	float f=1000.0;
	float n = 0.1;
	float z = (2 * n) / (f + n - texture2D( u_gDepth, coord ).x * (f - n));
	return z;
}

void main()
{
	vec2 uv = GetUv();
	vec3 normal = texture(u_gNormal, uv).xyz;
	vec3 position = texture(u_gPos, uv).xyz;

	vec3 lightPos = vec3(2000,1500,2000);
	vec3 lightDir = normalize(lightPos - position);
	float NdotL = dot(normalize(normal), lightDir);
	vec4 diffuse = vec4(0);
	if(NdotL > 0.0)
		diffuse = vec4(vec3(1,1,1)*NdotL, 1);

	color = texture(u_gColor, uv) * (vec4(0.2,0.2,0.2,0) + diffuse);
}
