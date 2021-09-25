#shader vertex
#version 330

layout(location = 0) in vec3 i_Positions;
layout(location = 1) in vec2 i_TexCoord;
layout(location = 2) in vec3 i_Normal;

uniform mat4 u_Mvp;
uniform mat4 u_M;
uniform vec2 u_TextureTiling;

out vec2 v_TexCoord;
flat out vec3 v_Normal;

void main()
{
	gl_Position = u_Mvp * vec4(i_Positions, 1.0);
	vec2 tilingClamped = max(vec2(0.1, 0.1), u_TextureTiling);
	v_TexCoord = i_TexCoord * tilingClamped;
	v_Normal = normalize(transpose(inverse(mat3(u_M))) * i_Normal);
}

#shader fragment
#version 330

out vec4 color;

in vec2 v_TexCoord;
flat in vec3 v_Normal;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 textureColor = vec4(1,1,1,1);
	if (textureSize(u_Texture, 0).x > 1) textureColor = texture2D(u_Texture, v_TexCoord);
	color = textureColor * u_Color;
}