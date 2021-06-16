#version 330

// TODO: Add color multiplier
uniform sampler2D uTexture;
uniform vec4 uColorMultiplier;

in vec2 fragTexCoord;

out vec4 outColor;

void main()
{
	vec4 textureColor = texture(uTexture, fragTexCoord);
	outColor = textureColor * uColorMultiplier;
}