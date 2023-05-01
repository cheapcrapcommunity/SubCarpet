#version 150

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec2 texcoord;

uniform sampler2DRect tex0;

out vec2 texCoordVarying;

void main()
{
    vec4 modifiedPosition = modelViewProjectionMatrix * position;
    
    float scale = 100;
    
    float displacementY = texture(tex0, texcoord).r;

	modifiedPosition.y += displacementY * scale;
	
    gl_Position = modifiedPosition;

    texCoordVarying = texcoord;
}
