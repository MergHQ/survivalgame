#version 400

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 u_mvp;
uniform mat4 u_2world;

out vec3 v_normal;
out vec3 v_pos;

void main()
{
	gl_Position = u_mvp*vec4(vertexPosition, 1.0);
	v_normal = (u_2world * vec4(normal, 0.0)).xyz;
	v_pos = (u_2world * vec4(vertexPosition, 1.0)).xyz;
}

@

#version 400

out vec4 color;

in vec3 v_normal;
in vec3 v_pos;

void main()
{
	vec3 lightPos = vec3(1000,500,1000);
	vec3 lightDir = normalize(lightPos - v_pos);
	float NdotL = dot(normalize(v_normal), lightDir);
	vec4 diffuse = vec4(0);
	if(NdotL > 0.0)
		diffuse = vec4(vec3(1,1,1)*NdotL, 1);

	vec4 c = vec4(0);

	color = texture() * (vec4(0.2,0.2,0.2,1) + diffuse);
}
