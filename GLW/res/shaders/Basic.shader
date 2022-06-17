#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;

uniform mat4 u_MVP;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;

void main()
{
	gl_Position = u_MVP* a_Position;
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
};



#shader fragment
#version 330 core

layout(location = 0) out vec4 o_Color;

uniform sampler2D u_Textures[32];

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

void main()
{
	// o_Color = texture(u_Texture, v_TexCoord);
	// o_Color = v_Color;
	int index = int(v_TexIndex);

	if (index == -1)
	{
		o_Color = v_Color;
		return;
	}
	o_Color = texture(u_Textures[index], v_TexCoord);
};