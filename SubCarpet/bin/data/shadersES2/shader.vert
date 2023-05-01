
// these are for the programmable pipeline system
uniform mat4 modelViewProjectionMatrix;
attribute vec4 position;
attribute vec2 texcoord;

uniform sampler2D tex0;

varying vec2 texCoordVarying;

void main()
{

    texCoordVarying = texcoord;

	vec4 modifiedPosition = modelViewProjectionMatrix * position;

    float scale = 100.0;
    
    float displacementY = texture2DLod(tex0, texCoordVarying.xy, 0.0).x;
		
    modifiedPosition.y += displacementY * scale;

	gl_Position = modifiedPosition;
}
