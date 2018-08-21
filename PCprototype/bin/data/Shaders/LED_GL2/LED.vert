#version 120

varying vec2 textureCoords;

void main()
{    
    textureCoords = gl_MultiTexCoord0.xy;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
