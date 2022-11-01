#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "renderer.hpp"
#include "vertexbuffer.hpp"
#include "indexbuffer.hpp"
#include "vertexarray.hpp"
#include "shader.hpp"
#include "texture.hpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
   
    glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    //GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    //const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
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
        -50.f, -50.f, 0.0f, 0.0f, // 0 (pos.x, pox.y, tex.x, tex.y)
        50.f, -50.f,  1.0f, 0.0f, // 1
        50.f, 50.f, 1.0f, 1.0f,   // 2
        -50.f, 50.f, 0.0f, 1.0f,  // 3
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


    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    Shader shader("res/shaders/basic.shader");
    shader.Bind();

    shader.SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 0.5f);
    
    Texture texture("res/textures/grid_0-1.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0); // match texture slot

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void) io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char *)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
    
    glm::vec3 translationA(200, 200, 0);
    glm::vec3 translationB(400, 200, 0);

    float r = 0.0f;
    float increment = 0.05f;

    glfwSetKeyCallback(window, key_callback);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
            glm::mat4 mvp = proj * view * model;
            shader.Bind();

            shader.SetUniform4f("u_Color", r, 0.2f, 0.7f, 0.125f);
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
            glm::mat4 mvp = proj * view * model;
            shader.Bind();

            shader.SetUniform4f("u_Color", r, 0.2f, 0.7f, 0.125f);
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);
 
        }

        increment = r > 1.0f ? -0.05f : (r < 0.0f ? 0.05f : increment);
        r += increment;
    
        {
            static int counter = 0;

            ImGui::Text("Hello, World!");
            ImGui::SliderFloat3("translation A", &translationA.x, 0.0f, 960.0f);
            ImGui::SliderFloat3("translation B", &translationB.x, 0.0f, 960.0f);
            ImGui::ColorEdit3("clear color", (float *)&clear_color);
            ImGui::Checkbox("Demo Window", &show_demo_window);
            ImGui::Checkbox("Another Window", &show_another_window);

            if (ImGui::Button("Button"))
                counter++;

            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
