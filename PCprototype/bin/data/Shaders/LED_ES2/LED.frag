precision highp float;

uniform sampler2D tex0;
uniform vec4 tintColor;
uniform vec2 resolution;
uniform float pixelSize;
varying vec2 textureCoords;
uniform bool pixelate;

void main(void)
{
    // Get the Texture Coordinates
    vec2 uv = textureCoords;

    // Get the Pixelated UVs
    if(pixelate)
        uv -= mod(uv, 1.0 / pixelSize);

    // Output the Texture Color with the Tint Color
    gl_FragColor = texture2D(tex0, uv) * tintColor;
}
