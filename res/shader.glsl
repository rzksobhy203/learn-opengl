#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 Color;
layout(location = 2) in vec2 TexCoord;

out vec3 v_Color;
out vec2 v_TexCoord;

void main()
{
	v_Color = Color;
	v_TexCoord = TexCoord;
	gl_Position = vec4(position.xy, 0.0f, 1.0f);
}

#shader fragment
#version 330 core

out vec4 color;

in vec3 v_Color;
in vec2 v_TexCoord;
uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, v_TexCoord) * vec4(v_Color.xyz, 1.0);
}
