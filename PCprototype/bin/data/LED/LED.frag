#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex0;
uniform float pixelSize;
uniform float resolutionW;
uniform float resolutionH;
uniform vec4 overlay;

void main(void)
{
	vec2 resolution = vec2(640.0,960.0);
	vec2 uv = gl_TexCoord[0].st;
	vec2 nUV = vec2(floor(uv.x / pixelSize) * pixelSize, floor(uv.y / pixelSize) * pixelSize);
	vec4 col = texture2DRect(tex0, nUV);
	col *= overlay;
    gl_FragColor = vec4(col.rgb,1.0);
}