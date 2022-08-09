#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 TexCoord;

out vec2 v_TexCoord;

void main()
{
	v_TexCoord = TexCoord;
	gl_Position = vec4(position.xy, 0.0f, 1.0f);
}

#shader fragment
#version 330 core

out vec4 color;

in vec2 v_TexCoord;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

void main()
{
	color = mix(texture(u_Texture2, v_TexCoord), texture(u_Texture1, v_TexCoord), 0.4);
}
