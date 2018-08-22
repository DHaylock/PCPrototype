#version 120

uniform sampler2DRect tex0;
uniform float pixelSize;
uniform vec2 resolution;
uniform vec4 tintColor;
varying vec2 textureCoords;

void main(void)
{
	// Get the Texture Coordinates
	vec2 pixelatedUVs = textureCoords;

	// Get the Pixelated UV's
	pixelatedUVs -= mod(pixelatedUVs,pixelSize);

	// Output the Texture Color with the Tint Color
    gl_FragColor = texture2DRect(tex0, pixelatedUVs) * tintColor;
}
