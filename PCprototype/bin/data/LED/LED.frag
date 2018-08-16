#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex0;
uniform float pixelSize;
uniform float resolutionW;
uniform float resolutionH;
uniform vec4 overlay;

float circle(in vec2 _st, in float _radius){
    vec2 dist = _st-vec2(0.5);
	return 1.-smoothstep(_radius-(_radius*0.01),
                         _radius+(_radius*0.01),
                         dot(dist,dist)*4.0);
}

void main(void)
{
	vec2 resolution = vec2(640.0,960.0);

	vec2 fuv = gl_TexCoord[0].st / resolution;

	fuv *= 25.0;

	fuv = fract(fuv);

	vec2 uv = gl_TexCoord[0].st;
	vec2 nUV = vec2(floor(uv.x / pixelSize) * pixelSize, floor(uv.y / pixelSize) * pixelSize);

	vec4 col = texture2DRect(tex0, nUV);
	col *= overlay;

	float d = circle(fuv,0.5);

    gl_FragColor = vec4(col.rgb,1.0);//col.rgb,1.0);
}