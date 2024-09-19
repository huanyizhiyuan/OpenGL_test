#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// 当用户改变窗口的大小的时候，视口也应该被调整
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

constexpr unsigned int width = 800;
constexpr unsigned int height = 600;

// 顶点着色器，glsl
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// 片段着色器，glsl
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // 注册这个函数，告诉GLFW我们希望每当窗口大小调整的时候调用这个函数。
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 使用glad前要先初始化！
    // GLFW给我们的是glfwGetProcAddress
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 1、着色器处理。
    // 我们要创建的顶点着色器类型。
    // 把这个着色器源码附加到着色器对象上，然后编译它
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // 检测glCompileShader是否编译成功。
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 片段着色器
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 着色器程序 并 链接着色器
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 检验链接是否成功。
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // 链接进程序，成功之后就可以把着色器对象删除了，没用了。
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // 2、顶点输入
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,     //左
    0.5f, -0.5f, 0.0f,      //右
    0.0f,  0.5f, 0.0f       //顶
    };

    // 顶点缓冲对象管理内存和顶点数组对象
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // 使用glBindVertexArray绑定VAO
    // 新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
    // 把之前定义的顶点数据复制到缓冲的内存中
    // 绑定和配置对应的VBO和属性指针，之后解绑VAO供之后使用
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 链接顶点属性，并且将VBO和VAO关联了起来。
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // VBO已经关联完毕，解绑了也不要紧。
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 虽然你可以在此时解绑 VAO，但这并不是必须的。一般情况下，在使用不同的 VAO 时，
    // 必须显式调用 glBindVertexArray 来重新绑定它，所以如果不解绑，后续的 VAO 调用也不会修改当前 VAO。
    // 因此，解绑 VAO 并不常见。
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}