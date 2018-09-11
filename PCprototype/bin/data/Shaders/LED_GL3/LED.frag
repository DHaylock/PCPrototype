#version 330

in vec2 textureCoords;
out vec4 outputColor;

uniform sampler2DRect tex0;
uniform vec4 tintColor;

uniform vec2 resolution;
uniform float pixelSize;
uniform bool pixelate;

void main(void)
{
	// Get the Texture Coordinates
	vec2 uv = textureCoords;

    // Get the Pixelated UV's
    if(pixelate)
        uv -= mod(uv,pixelSize);

	// Output the Texture Color with the Tint Color
    outputColor = texture(tex0, uv) * tintColor;
}
