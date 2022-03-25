#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//acá va el codigo que antes estaba en main
	//Comienza el pipeline vertexShader -> shape assembly -> geometry shader -> rasterazation -> fragment shader -> test and blending
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create Vertex Shader Object and get its reference
	glShaderSource(vertexShader, 1, &vertexSource, NULL); // Attach Vertex Shader source to the Vertex Shader Object
	glCompileShader(vertexShader); // Compile the Vertex Shader into machine code

	//el fragment shader es toda la informacion necesaria para poder renderizar un pixel en la pantalla (basicamente color y luces)
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create Fragment Shader Object and get its reference
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL); // Attach Fragment Shader source to the Fragment Shader Object
	glCompileShader(fragmentShader); // Compile the Vertex Shader into machine code

	ID = glCreateProgram(); // Create Shader Program Object and get its reference
	glAttachShader(ID, vertexShader); // Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, fragmentShader);

	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);

	glDeleteShader(vertexShader); // Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}