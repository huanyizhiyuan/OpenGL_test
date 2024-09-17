#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// 当用户改变窗口的大小的时候，视口也应该被调整
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

constexpr int width = 800;
constexpr int height = 600;

int main()
{
    glfwInit();
    // 主版本号(Major)和次版本号(Minor)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 核心模式(Core-profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // glfwCreateWindow 宽，高，标题。后两个暂时不管。
    // 返回一个GLFWwindow对象。
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 使用glad前要先初始化！
    // GLFW给我们的是glfwGetProcAddress
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 注册这个函数，告诉GLFW我们希望每当窗口大小调整的时候调用这个函数。
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 渲染循环，在我们希望程序关闭之前，一直运行程序。
    /*
        1、glfwWindowShouldClose(window)：检查GLFW是否被要求退出。
        2、glfwPollEvents：检查有没有触发什么事件。
        3、glfwSwapBuffers：会交换颜色缓冲，简而言之就是绘制，并显示。
    */
    while (!glfwWindowShouldClose(window))
    {
        // 输入:检测用户动作
        processInput(window);

        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 检查并调用事件，交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //释放资源
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