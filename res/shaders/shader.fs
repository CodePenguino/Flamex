#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D Tex;

void main()
{
	vec4 texColor = texture2D(Tex, TexCoord);

	FragColor = texColor;
}
