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
layout(location = 0) out vec4 gColor;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec3 gPos;

in vec3 v_normal;
in vec3 v_pos;

void main()
{
	gNormal = v_normal;
	gPos = v_pos;
	if(v_pos.y < 3+sin(v_normal.y) * 5)
		gColor = vec4(1,1,0,1);
	else if(v_pos.y < 20+sin(v_normal.y) * 5)
		gColor = vec4(0.1,0.5,0.1,1);
	else
		gColor = vec4(1);
}
