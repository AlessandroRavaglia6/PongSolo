#version 430

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

//out vec3 fPosition;
out vec3 fNormal;
out vec4 fColor;
out flat int instanceID;
out vec3 light_dir;

uniform mat4 MVP[2];
uniform vec4 vColor[2];
uniform vec3 v_light_direction;

void main()
{
	mat4 scale = mat4(  0.5f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.5f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.5f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f );

	// rotate
	float rot_ang = -1.0f;
	mat4 rotate_1 = mat4( cos(rot_ang), 0.0f, sin(rot_ang), 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						-sin(rot_ang), 0.0f, cos(rot_ang), 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);
	//rot_ang = 1.40f;
	rot_ang = 0.0f;
	mat4 rotate_2 = mat4( cos(rot_ang), -sin(rot_ang), 0.0f, 0.0f,
						sin(rot_ang), cos(rot_ang), 0.0f, 0.0f,
						0.0f, 0.0f, 0.1f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);
	mat4 rotate = rotate_2 * rotate_1;
	
	//gl_Position = rotate * scale * vec4(vPosition, 1.0f);
	//gl_Position = rotate * vec4(vPosition, 1.0f);
	//gl_Position = scale * vec4(vPosition, 1.0f);
	//gl_Position = vec4(vPosition, 1.0f);


	instanceID = gl_InstanceID;
	
	gl_Position = MVP[gl_InstanceID] * vec4(vPosition, 1.0f);

	mat3 MVPN = mat3(MVP[gl_InstanceID][0].x, MVP[gl_InstanceID][0].y, MVP[gl_InstanceID][0].z,
					 MVP[gl_InstanceID][1].x, MVP[gl_InstanceID][1].y, MVP[gl_InstanceID][1].z,
					 MVP[gl_InstanceID][2].x, MVP[gl_InstanceID][2].y, MVP[gl_InstanceID][2].z);

	fNormal = normalize(MVPN * vNormal);
	fColor = vColor[gl_InstanceID];
	light_dir = v_light_direction;
}