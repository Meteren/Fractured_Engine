#version 450 core

in vec2 uv;
out vec4 color;

uniform vec4 u_color;
uniform sampler2D mainTex;

void main(){
	vec4 sampledTex = texture(mainTex,uv);
	color = sampledTex;
}