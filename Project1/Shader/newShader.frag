#version 130

in vec4 fragmentColor;
in vec4 fragmentpos;
in vec2 fragmentUV;

out vec4 color;

uniform vec3 light_pos;
uniform vec4 colour;
uniform sampler2D sampler_1;

//uniform float time;

void main(){
	//color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
	//color = fragmentColor;
	float intensity;
	if(light_pos != vec3(0.0f,0.0f,0.0f)){
		intensity = 1.0f / length(fragmentpos.xyz*3 - light_pos);
	}
	else{
		intensity = 1.0f;
	}
	
	if(colour != vec4(0.0,0.0,0.0,0.0)){
		color = colour * intensity;
	}
	else{
		//color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
		color = fragmentColor;
	}
	color = texture(sampler_1, fragmentUV) * color;
	/*
	if((time - fragmentpos.x + 3.0f)/(fragmentpos.x + 3.0f) < 0.0f)
		color.a = 0.0f;
	else if( (time - fragmentpos.x + 3.0f)/(fragmentpos.x + 3.0f) < 1.0f)
		color.a *= (time - fragmentpos.x + 3.0f)/(fragmentpos.x + 3.0f);
	else
		color.a = color.a;
	*/
}