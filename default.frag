#version 330 core
out vec4 FragColor;

in vec3 color;

void main()
{

	//ahora serán enviados directamente a través de color
   FragColor = vec4(color, 1.0f);
}