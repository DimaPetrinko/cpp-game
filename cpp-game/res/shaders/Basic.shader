#shader vertex
#version 330

layout(location = 0) in vec2 i_Position;
layout(location = 1) in vec2 i_TexCoord;

uniform mat4 u_MP;

out vec2 o_TexCoord;

void main()
{
	gl_Position = u_MP * vec4(i_Position, 0, 1);
	o_TexCoord = i_TexCoord;
}

#shader fragment
#version 330

out vec4 color;

in vec2 i_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 textureColor = vec4(1,1,1,1);
	// if (u_Texture) textureColor = texture2D(u_Texture, i_TexCoord);
	// else textureColor = vec4(1, 1, 1, 1);
	color = textureColor * u_Color;
}