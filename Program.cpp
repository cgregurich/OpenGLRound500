#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define BG_COLOR 0.28f, 0.07f, 0.44f, 1.0f
#define ARRAY_LEN(arr) (sizeof(arr)/sizeof(arr[0]))

void updateVertices();
void moveRight();
void moveLeft();
void moveUp();
void moveDown();

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, 1.0, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

float vertices[] = {
    -.5f, .75f,
    -.25f, .125f,
    -.75f, .125f
};


void framebuffer_size_callback(GLFWwindow* window, int height, int width)
{
    glViewport(0, 0, width, height);
}

bool arrowKeyPressed(GLFWwindow *window)
{
    unsigned int result = 0;
    result |= glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
    result |= glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
    result |= glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
    result |= glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
    return result;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        updateVertices();
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        moveRight();
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        moveLeft();
    }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        moveUp();
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        moveDown();
    }
}

const float moveSpeed = 0.0001f;
void moveRight()
{
    for (int i=0; i<ARRAY_LEN(vertices); i+=2)
    {
        vertices[i] += moveSpeed;
    }
}

void moveLeft()
{
    for (int i=0; i<ARRAY_LEN(vertices); i+=2)
    {
        vertices[i] -= moveSpeed;
    }
}

void moveUp()
{
    for (int i=1; i<ARRAY_LEN(vertices); i+=2)
    {
        vertices[i] += moveSpeed;
    }
}

void moveDown()
{
    for (int i=1; i<ARRAY_LEN(vertices); i+=2)
    {
        vertices[i] -= moveSpeed;
    }
}

void updateVertices()
{
    vertices[0] += 0.01f;
}

unsigned int makeShaderProgram()
{
    int success;
    char infoLog[512];

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
} /* makeShaderProgram() */

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int shaderProgram = makeShaderProgram();
    
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(BG_COLOR);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;



    return 0;
}
