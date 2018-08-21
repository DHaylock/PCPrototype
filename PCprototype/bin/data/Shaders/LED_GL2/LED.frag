#version 120

uniform sampler2DRect tex0;
uniform float pixelSize;
uniform vec2 resolution;
uniform vec4 tintColor;
uniform float vignetteAmount;

varying vec2 textureCoords;

void main(void)
{
	vec2 vUV = vec2(floor(textureCoords / pixelSize) * pixelSize);
	vec4 color = texture2DRect(tex0, vUV);

	vec2 cUV = textureCoords / resolution;
	float dist = 1.0 - distance(cUV,vec2(0.5)) * vignetteAmount;

    gl_FragColor = color * (dist * tintColor);
}