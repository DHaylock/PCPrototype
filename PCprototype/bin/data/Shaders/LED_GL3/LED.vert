#version 330
uniform mat4 modelViewProjectionMatrix;

in vec2 texcoord;
in vec4 position;
out vec2 textureCoords;

void main()
{
    textureCoords = texcoord;
	gl_Position = modelViewProjectionMatrix * position;
}
