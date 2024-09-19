#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// ���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

constexpr unsigned int width = 800;
constexpr unsigned int height = 600;

// ������ɫ����glsl
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   gl_PointSize = 30.0f;\n"
"}\0";


// Ƭ����ɫ����glsl
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
    // ע���������������GLFW����ϣ��ÿ�����ڴ�С������ʱ��������������
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ʹ��gladǰҪ�ȳ�ʼ����
    // GLFW�����ǵ���glfwGetProcAddress
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ���� GL_PROGRAM_POINT_SIZE���Ա��ڶ�����ɫ�������� gl_PointSize
    glEnable(GL_PROGRAM_POINT_SIZE);

    // 1����ɫ������
    // ����Ҫ�����Ķ�����ɫ�����͡�
    // �������ɫ��Դ�븽�ӵ���ɫ�������ϣ�Ȼ�������
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // ���glCompileShader�Ƿ����ɹ���
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Ƭ����ɫ��
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ��ɫ������ �� ������ɫ��
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // ���������Ƿ�ɹ���
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // ���ӽ����򣬳ɹ�֮��Ϳ��԰���ɫ������ɾ���ˣ�û���ˡ�
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // 2����������
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,     //��
    0.5f, -0.5f, 0.0f,      //��
    0.0f,  0.5f, 0.0f       //��
    };

    // ���㻺���������ڴ�Ͷ����������
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // ʹ��glBindVertexArray��VAO
    // �´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
    // ��֮ǰ����Ķ������ݸ��Ƶ�������ڴ���
    // �󶨺����ö�Ӧ��VBO������ָ�룬֮����VAO��֮��ʹ��
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ���Ӷ������ԣ����ҽ�VBO��VAO������������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // VBO�Ѿ�������ϣ������Ҳ��Ҫ����
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // ��Ȼ������ڴ�ʱ��� VAO�����Ⲣ���Ǳ���ġ�һ������£���ʹ�ò�ͬ�� VAO ʱ��
    // ������ʽ���� glBindVertexArray �����°����������������󣬺����� VAO ����Ҳ�����޸ĵ�ǰ VAO��
    // ��ˣ���� VAO ����������
    glBindVertexArray(0);

    // �����С����Ϊ 10.0
    //glPointSize(10.0f);

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
        // void glDrawArrays(GLenum mode, GLint first, GLsizei count);
        /*
            mode�����Ƶ�ͼԪ����
            first�����ĸ����㿪ʼ������ָ������Ҫ���Ƶĵ�һ�������ڶ��������е�������ͨ���� 0����ʾ�ӵ�һ�����㿪ʼ����
            count����Ҫ���ƵĶ���������
            �㣬��Ҫע��һ�£�һ��Ҫ���ô�С��
            ���Էŵ�glsl�
        */
        glDrawArrays(GL_POINTS, 0, 3);
        //���Ƿ���β����
        //glDrawArrays(GL_LINE_STRIP, 0, 3);
        glDrawArrays(GL_LINE_LOOP, 0, 3);

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