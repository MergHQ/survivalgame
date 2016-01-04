float AmbientOcclusion(vec2 uv)
{
	vec2 noiseScale = vec2(u_width/4.0, u_height/4.0);
	vec3 normal = texture(u_gViewNormal, uv).xyz;
	vec3 fragPos = texture(u_gViewPosDepth, uv).xyz;
	vec3 randomVec = texture(u_noiseTexture, uv * noiseScale).xyz;  
	vec3 tangent = normalize(vec3(randomVec - normal * dot(randomVec, normal)));
	vec3 bitan = cross(normal, tangent);
	mat3 tbn = mat3(tangent, bitan, normal);

	float occlusion = 0.0;
	for(int i = 0; i < 64; ++i)
	{
		vec3 dsample = tbn * u_ssaoKernel[i];
		dsample = fragPos + dsample * u_ssaoRadius;

		vec4 offset = u_projMat * vec4(dsample, 1.0);
		offset.xy /= offset.w;
		offset.xy = offset.xy * 0.5 + 0.5;

		float sampleDepth = -texture(u_gViewPosDepth, offset.xy).w;
		if(sampleDepth - dsample.z > 0.5)
		{
			float rangeCheck = smoothstep(0.0, 1.0, u_ssaoRadius / abs(fragPos.z - sampleDepth));
			occlusion += (sampleDepth >= dsample.z ? 1.0 : 0.0) * rangeCheck;  
		} 
	}
	occlusion = 1.0-(occlusion / float(64));
	return pow(occlusion,1);
}