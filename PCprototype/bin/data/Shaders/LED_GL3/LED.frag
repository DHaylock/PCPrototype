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
	vec2 pixelatedUVs = vec2(floor(textureCoords / pixelSize) * pixelSize);

	// Get the Texture Color at the pixelated UV coordinate
	vec4 textureColor = texture(tex0, pixelatedUVs);

	// Remap the UV's
	vec2 remappedUVs = textureCoords / resolution;

	// Create a Vignette
	float dist = 1.0 - distance(remappedUVs,vec2(0.5)) * vignetteAmount;

	// Output the Texture Color with the Tint Color
    outputColor = (textureColor * tintColor) * dist;
}