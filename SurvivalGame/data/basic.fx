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
	vec3 lightPos = vec3(100,100,100);
	vec3 lightDir = normalize(lightPos - v_pos);
	float multiplier = dot(normalize(v_normal), lightDir);

	color = vec4(0.1,0.5,0.1,1) * multiplier + vec4(vec3(0.05),1);
}
