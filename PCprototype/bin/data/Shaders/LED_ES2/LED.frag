precision highp float;

uniform sampler2D tex0;
uniform vec4 tintColor;
uniform vec2 resolution;
uniform float pixelSize;
varying vec2 textureCoords;

void main(void)
{
		// Get the Texture Coordinates
        vec2 pixelatedUVs = textureCoords;

		// Get the Pixelated UVs
        pixelatedUVs -= mod(pixelatedUVs, 1.0 / pixelSize);

        // Output the Texture Color with the Tint Color
        gl_FragColor = texture2D(tex0, pixelatedUVs) * tintColor;
}
