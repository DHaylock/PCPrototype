uniform mat4 modelViewProjectionMatrix;

attribute vec2 texcoord;
attribute vec4 position;
varying vec2 textureCoords;

void main()
{
    textureCoords = texcoord;
	gl_Position = modelViewProjectionMatrix * position;
}
