#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderer.hpp"
#include "vertexbuffer.hpp"
#include "indexbuffer.hpp"
#include "vertexarray.hpp"
#include "shader.hpp"
#include "texture.hpp"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
   
    glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    unsigned int err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "Error!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl;
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
        0.5f, -0.5f,  1.0f, 0.0f, // 1
        0.5f, 0.5f, 1.0f, 1.0f,   // 2
        -0.5f, 0.5f, 0.0f, 1.0f,  // 3
    };
   
    unsigned int indices[] = {
        0, 1, 2,  // first triangle vertices
        2, 3, 0   // second triangle vertices
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    Shader shader("res/shaders/basic.shader");
    shader.Bind();

    shader.SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);

    Texture texture("res/textures/Octocat.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0); // match texture slot

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    float r = 0.0f;
    float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();
        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.2f, 0.7f, 1.0f);

        renderer.Draw(va, ib, shader);

        
        increment = r > 1.0f ? -0.05f : (r < 0.0f ? 0.05f : increment);
        r += increment;
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
