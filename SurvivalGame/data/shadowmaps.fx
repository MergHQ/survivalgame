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
layout(location = 0) out float fragmentdepth;


void main()
{
	fragmentdepth = gl_FragCoord.z;
}
