#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// ���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

constexpr int width = 800;
constexpr int height = 600;

int main()
{
    glfwInit();
    // ���汾��(Major)�ʹΰ汾��(Minor)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // ����ģʽ(Core-profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // glfwCreateWindow ���ߣ����⡣��������ʱ���ܡ�
    // ����һ��GLFWwindow����
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // ʹ��gladǰҪ�ȳ�ʼ����
    // GLFW�����ǵ���glfwGetProcAddress
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ע���������������GLFW����ϣ��ÿ�����ڴ�С������ʱ��������������
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ��Ⱦѭ����������ϣ������ر�֮ǰ��һֱ���г���
    /*
        1��glfwWindowShouldClose(window)�����GLFW�Ƿ�Ҫ���˳���
        2��glfwPollEvents�������û�д���ʲô�¼���
        3��glfwSwapBuffers���ύ����ɫ���壬�����֮���ǻ��ƣ�����ʾ��
    */
    while (!glfwWindowShouldClose(window))
    {
        // ����:����û�����
        processInput(window);

        // ��Ⱦָ��
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ��鲢�����¼�����������
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //�ͷ���Դ
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