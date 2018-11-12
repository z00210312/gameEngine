#version 130

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec4 fragmentpos;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 ortho;

void main(){
	gl_Position.xy = vertexPosition;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;
	gl_Position = ortho * gl_Position;
	fragmentColor = vertexColor;
	fragmentpos = gl_Position;
	fragmentUV = vertexUV;
}