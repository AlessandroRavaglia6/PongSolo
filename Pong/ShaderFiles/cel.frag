#version 430

in vec4 fColor;
in vec3 fNormal;

out vec4 f_Color;

void main ()
{
	vec3 light_direction = vec3(-0.2f, 0.0f, -0.6f);
	light_direction = normalize(light_direction);

	float angle = clamp(dot(light_direction, normalize(fNormal)), 0, 1);

	if (angle < 0.25f)
	{
		angle = 0.25f;
	} 
	else if (angle < 0.5f)
	{
		angle = 0.5f;
	}
	else if (angle < 0.75f)
	{
		angle = 0.75;
	}
	else
	{
		angle = 1.0f;
	}

	float fac = 0.5f;
	angle = angle * fac;

	float ambient = 0.1f;

	vec4 color = vec4(  fColor.x * (angle + ambient),
						fColor.y * (angle + ambient),
						fColor.z * (angle + ambient), 1.0f);

	// Outlining
	vec3 front_direction = vec3(0.0f, 0.0f, -1.0f);
	front_direction = normalize(front_direction);

	angle = dot(front_direction, normalize(fNormal));
	float line_width = 0.2f;

	if (abs(angle) < line_width)
	{
		color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	f_Color = color;
}