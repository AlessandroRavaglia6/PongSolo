#version 430

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

out flat vec4 fColor;

void main()
{
	mat4 scale = mat4(  0.5f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.5f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.5f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f );
	
	gl_Position = scale * vec4(vPosition, 1.0f);
	//gl_Position = vec4(vPosition, 1.0f);

	vec3 light_direction = vec3(-0.2f, 0.0f, -0.6f);
	light_direction = normalize(light_direction);

	float angle = clamp(dot(light_direction, normalize(vNormal)), 0, 1);
	angle = angle * 0.5f;

	float ambient = 0.0f;

	vec3 color = vec3(1.0f, 1.0f, 1.0f);

	fColor = vec4(  color.x * (angle + ambient),
					color.y * (angle + ambient),
					color.z * (angle + ambient), 1.0f);
}