#version 330 core
out vec4 FragColor;

in vec3 color;

void main()
{

	//ahora ser�n enviados directamente a trav�s de color
   FragColor = vec4(color, 1.0f);
}