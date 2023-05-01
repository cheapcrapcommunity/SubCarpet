#version 120

uniform sampler2DRect tex0;

varying vec2 texCoordVarying;

void main()
{

    texCoordVarying = gl_MultiTexCoord0.xy;

    vec4 position = ftransform();
    vec4 modifiedPosition = position;

    float scale = 100;
    
    float displacementY = texture2DRect(tex0, texCoordVarying).x;
		
    modifiedPosition.y += displacementY * scale;

	gl_Position = modifiedPosition;
}
