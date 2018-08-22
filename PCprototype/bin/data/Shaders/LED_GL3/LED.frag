#version 330

in vec2 textureCoords;
out vec4 outputColor;

uniform sampler2DRect tex0;
uniform vec4 tintColor;

uniform vec2 resolution;
uniform float pixelSize;
uniform float vignetteAmount;

void main(void)
{
	// Pixelate the UV coords
	//vec2 pixelatedUVs = vec2(floor(textureCoords / pixelSize) * pixelSize);

	// Get the Texture Coordinates
	vec2 pixelatedUVs = textureCoords;

	// Get the Pixelated UV's
	pixelatedUVs -= mod(pixelatedUVs,pixelSize);

	// Output the Texture Color with the Tint Color
    outputColor = texture(tex0, pixelatedUVs) * tintColor;
}
