precision highp float;

uniform sampler2D tex0;
uniform vec4 tintColor;
uniform vec2 resolution;
uniform float pixelSize;
uniform float vignetteAmount;

in vec2 textureCoords;

void main(void)
{
	// Pixelate the UV coords
	vec2 pixelatedUVs = vec2(floor(textureCoords / pixelSize) * pixelSize);

	// Get the Texture Color at the pixelated UV coordinate
	vec4 textureColor = texture2D(tex0, pixelatedUVs);

	// Remap the UV's
	vec2 remappedUVs = textureCoords / resolution;

	// Create a Vignette
	float dist = 1.0 - distance(remappedUVs,vec2(0.5)) * vignetteAmount;

	// Output the Texture Color with the Tint Color
    gl_FragColor = (textureColor * tintColor) * dist;
}
