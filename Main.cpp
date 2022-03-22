#include <iostream>
#include <glad/glad.h>  // se importa primero GLAD y luego GLFW
#include <GLFW/glfw3.h>



//Lo siguiente es copiado textual para usar Vertex Shaders
//esto deja los valores de las ventanas entre -1 y 1
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";



int main()
{
	glfwInit();  //Inicia el objeto para la ventana
 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //Le dice a glfw la version usada
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  //minima y maxima
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //el tipo de perfil (core = Moderno)


	GLfloat vertices[] =
	{
		-0.5f, 0.5f, 0.0f, // esquina superior izquierda x = -1 y = 1
		-0.5f, -0.5f, 0.0f, // esquina inferior izquierda x = -1 y = -1
		0.5f, -0.5f, 0.0f, // esquina inferior derecha x = 1, y = -1
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};


	GLFWwindow* window = glfwCreateWindow(800, 800, "Programa 1", NULL, NULL);  //ancho, alto, nombre, fullscrin, no importa
	
	if (!window) { //revisar si falla al crearse
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);  //agrega la ventana en el contexto actual



	//CODIGO de manipulacion

	gladLoadGL();  //carga GLAD para que esta configure OpenGL (que recordar, es una maquina de estados)

	glViewport(0, 0, 800, 800);  //especificar rango de vista de OpenGL en la ventana, en este caso va desde
								 // x = 0, y = 0, hasta x = 800, y = 800

	//Comienza el pipeline vertexShader -> shape assembly -> geometry shader -> rasterazation -> fragment shader -> test and blending
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create Vertex Shader Object and get its reference
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Attach Vertex Shader source to the Vertex Shader Object
	glCompileShader(vertexShader); // Compile the Vertex Shader into machine code
	
	//el fragment shader es toda la informacion necesaria para poder renderizar un pixel en la pantalla (basicamente color y luces)
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create Fragment Shader Object and get its reference
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Attach Fragment Shader source to the Fragment Shader Object
	glCompileShader(fragmentShader); // Compile the Vertex Shader into machine code
	
	GLuint shaderProgram = glCreateProgram(); // Create Shader Program Object and get its reference
	glAttachShader(shaderProgram, vertexShader); // Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, fragmentShader);
	
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram); 

	glDeleteShader(vertexShader); // Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(fragmentShader);

	GLuint VAO, VBO;  //Crear contenedor de referencias para el Vertex Array Object y el Vertex Buffer Object

	glGenVertexArrays(1, &VAO);  //Generar el VAO y VBO con solo 1 objeto cada 1 
	glGenBuffers(1, &VBO);  //generar primero VAO y luego VBO

	glBindVertexArray(VAO);  // Hacer que VAO sea el Vertex Array Object by binding it

	glBindBuffer(GL_ARRAY_BUFFER, VBO);  // Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // Introduce los vertices a el VBO

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);  //Configura los atributos del vertice de manera que OpenGL sepa como leer el VBO
	glEnableVertexAttribArray(0);  //Habilita el atributo de vertice que permite a OpenGL saber como usarlo

	glBindBuffer(GL_ARRAY_BUFFER, 0);  //bind tanto el VBO y el VAO a 0, de forma que no modifiquemos el VAO o VBO que creamos
	glBindVertexArray(0);


	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);  //Especificar color del fondo
	glClear(GL_COLOR_BUFFER_BIT);  //Limpiar el back buffer y asignarle el nuevo color
	glfwSwapBuffers(window);  //Cambiar buffer trasero por el frontal

	while (!glfwWindowShouldClose(window)) {  //Main while loop
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);  //Especificar color del fondo
		glClear(GL_COLOR_BUFFER_BIT);  //Limpiar el back buffer y asignarle el nuevo color
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(window);
		glfwPollEvents();  //se encarga de todos los eventos de GLFW
	}

	glfwDestroyWindow(window);  //eliminar ventana antes de cerrarla
	glfwTerminate();  //terminar GLFW antes de cerrar el programa

	//FINCODIGO
	return 0;
}