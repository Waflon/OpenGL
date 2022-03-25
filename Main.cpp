#include <iostream>
#include <glad/glad.h>  // se importa primero GLAD y luego GLFW
#include <GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

GLfloat vertices[] =
{
	//COORDINATES					// COLORS
	-0.5f, -0.5f, 0.0f,				 0.5f, 0.5f, 0.02f,
	0.5f, -0.5f, 0.0f,				 0.8f, 0.4f, 0.12f,
	0.5f, 0.5f, 0.0f,				 0.0f, 0.6f, 0.32f,
	-0.5f, 0.5f, 0.0f,				 0.7f, 0.45f, 0.5f
};

GLint indices[] =
{
	0, 1, 3,
	1, 3, 2
};

int main()
{
	glfwInit();  //Inicia el objeto para la ventana
 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //Le dice a glfw la version usada
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  //minima y maxima
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //el tipo de perfil (core = Moderno)


	GLFWwindow* window = glfwCreateWindow(800, 800, "Programa 1", NULL, NULL);  //ancho, alto, nombre, fullscrin, no importa
	
	if (!window) { //revisar si falla al crearse
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);  //agrega la ventana en el contexto actual

	gladLoadGL();  //carga GLAD para que esta configure OpenGL (que recordar, es una maquina de estados)

	glViewport(0, 0, 800, 800);  //especificar rango de vista de OpenGL en la ventana, en este caso va desde
								 // x = 0, y = 0, hasta x = 800, y = 800

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	while (!glfwWindowShouldClose(window)) {  //Main while loop
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);  //Especificar color del fondo
		glClear(GL_COLOR_BUFFER_BIT);  //Limpiar el back buffer y asignarle el nuevo color
		shaderProgram.Activate();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();  //se encarga de todos los eventos de GLFW
	}

	//ELIMINAR OBJETOS CREADOS
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	
	//ELIMINAR VENTANAS ANTES DE CERRAR EL PROGRAMA
	glfwDestroyWindow(window); 
	glfwTerminate();  //terminar GLFW antes de cerrar el programa

	return 0;
}