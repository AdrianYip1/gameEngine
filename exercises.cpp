#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <enginemath/vec3.hpp>
#include <shader/shader.hpp>

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "uniform vec4 horizOffset;\n"
    "out vec3 ourColor;\n"
	"void main()\n"
	"{\n"
	" gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0) + horizOffset;\n"
    " ourColor = aColor;"
	"}\0";


const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
	"void main()\n"
	"{\n"
	" FragColor = vec4(ourColor, 1.0f);\n"
	"}\0";

float vertices[] = {
// positions // colors
0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
};



void framebuffer_size_callback(GLFWwindow* window, int width, int  height) { 
    glViewport(0, 0, width, height); 
};

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
};

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    // glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initalize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 500, 500);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Exercise 1: draw 2 triangles next to each other using glDrawArrays by 
    // adding more vertices

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //VAO
    glBindVertexArray(VAO);

    //VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    

	//Vertex Shader object
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Fragment Shader Object
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	//Linking the vertex and fragment shaders together
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
    


	//Delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

    float offset = 0.0f;
    float direction = 0.0001f;

    // Render Loop
    while (!glfwWindowShouldClose(window)) {
		processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        offset += direction;
        if (offset > 0.2f || offset < -0.2f)
            direction = -direction;

        int offsetLocation = glGetUniformLocation(shaderProgram, "horizOffset");
        glUniform4f(offsetLocation, offset, 0.0f, 0.0f, 0.0f);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
    }
	
    glfwTerminate();
	return 0;
}


