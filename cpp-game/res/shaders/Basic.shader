#shader vertex
#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 uProjection;
uniform vec2 uPosition;
uniform vec2 uSize;

out vec2 oTextCoord;

void main()
{
	vec2 modifiedPosition = (position * uSize) + uPosition;
	gl_Position = uProjection * vec4(modifiedPosition, 1.0, 1.0);
	oTextCoord = texCoord;
}

#shader fragment
#version 330

out vec4 color;

in vec2 textCoord;

uniform vec4 uColor;
uniform sampler2D uTexture;

void main()
{
	vec4 textureColor;
	if (uTexture) textureColor = texture2D(uTexture, textCoord);
	else textureColor = vec4(1,1,1,1);
	color = textureColor * uColor;
}