#version 120

uniform sampler2DRect tex0;
uniform float pixelSize;
uniform vec2 resolution;
uniform vec4 tintColor;
varying vec2 textureCoords;
uniform bool pixelate;

void main(void)
{
	// Get the Texture Coordinates
	vec2 uv = textureCoords;

	// Get the Pixelated UV's
    if(pixelate)
        uv -= mod(uv,pixelSize);

	// Output the Texture Color with the Tint Color
    gl_FragColor = texture2DRect(tex0, uv) * tintColor;
}
