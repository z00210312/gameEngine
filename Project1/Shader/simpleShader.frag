#version 130

in vec4 fragmentColor;
in vec4 fragmentpos;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D sampler_1;

void main(){
	color = fragmentColor;
	color = texture(sampler_1, fragmentUV) * color;
}