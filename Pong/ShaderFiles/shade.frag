#version 430

in vec4 fColor;
in vec3 fNormal;

out vec4 f_Color;

void main ()
{
	//vec3 light_direction = vec3(-0.2f, 0.0f, -0.6f);
	vec3 light_direction = vec3(-0.1f, 0.3f, 0.3f);
	light_direction = normalize(light_direction);

	float angle = clamp(dot(light_direction, normalize(fNormal)), 0, 1);
	angle = angle * 0.5f;

	float ambient = 0.1f;

	f_Color = vec4( fColor.x * (angle + ambient),
					fColor.y * (angle + ambient),
					fColor.z * (angle + ambient), 1.0f);
}