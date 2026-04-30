#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <enginemath/vec3.hpp>

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";


const char *fragmentShaderSource1 = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	" FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	" FragColor = vec4(0.2f, 0.2f, 0.7f, 1.0f);\n"
	"}\0";

float vertices[] = {
    0.0f, 0.0f, 0.0f, 
    0.3f, 0.0f, 0.0f, 
    0.3f, 0.3f, 0.0f, 
    0.0f, 0.3f, 0.0f,
    -0.3f, 0.0f, 0.0f,
    0.6f, 0.3f, 0.0f
};

unsigned int indices_1[] = {
    4, 0, 3,
    0, 1, 2
};

unsigned int indices_2[] = {
    0, 2, 3,
    1, 2, 5
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

    GLFWwindow* window = glfwCreateWindow(2560, 1440, "OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    // glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initalize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 2560, 1440);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Exercise 1: draw 2 triangles next to each other using glDrawArrays by 
    // adding more vertices

    unsigned int VBO1, VBO2, VAO1, VAO2, EBO1, EBO2;
    glGenVertexArrays(1, &VAO1);
    glGenVertexArrays(1, &VAO2);

    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &VBO2);

    glGenBuffers(1, &EBO1);
    glGenBuffers(1, &EBO2);

    //VAO
    glBindVertexArray(VAO1);

    //VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_1), indices_1, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    //VAO
    glBindVertexArray(VAO2);

    //VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_2), indices_2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    
    //Shaders
    unsigned int vertexShader, fragmentShader1, shaderProgram1, fragmentShader2, shaderProgram2;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    shaderProgram1 = glCreateProgram();
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    shaderProgram2 = glCreateProgram();

    //Vertex Shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Fragment Shader
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader1);

    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    //Link Shaders
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);

    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);


    //Delete Shader Objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShader2);

    // Render Loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glUseProgram(shaderProgram1);
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	
    glfwTerminate();
	return 0;
}


