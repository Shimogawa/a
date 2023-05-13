#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_NATIVE_INCLUDE_NONE
#include "glad/glad.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "logic/events.hpp"
#include "utils/safeq.hpp"

#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>

void initImgui(GLFWwindow* window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 130");
  io.Fonts->AddFontFromFileTTF("./res/Ubuntu.ttf", 18.0f);
}

void cleanUp(GLFWwindow* window) {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(window);
  glfwTerminate();
}

static int fc = 0;

void imguiFrame() {
  ImGui_ImplGlfw_NewFrame();
  ImGui_ImplOpenGL3_NewFrame();

  ImGui::NewFrame();

  // ImGui::ShowDemoWindow(nullptr);
  {
    ImGui::Begin("info");
    auto&& io = ImGui::GetIO();
    ImGui::Text("F# %d, FR %.2f, DT %.2f", fc, io.Framerate, 1000.0f / io.Framerate);
    ImGui::End();
  }

  ImGui::Render();
}

void renderLoop(GLFWwindow* window) {
  glfwMakeContextCurrent(nullptr);

  std::thread t(
    [window]() {
      // glfwMakeContextCurrent(window);
      while (!glfwWindowShouldClose(window)) {
        // deal with events
        glfwMakeContextCurrent(nullptr);
        processEvents();
        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
        fc++;

        imguiFrame();

        // GLuint VBO;
        // glGenBuffers(1, &VBO);
        // glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // float vertices[] = {
        //   -0.5f, -0.5f, 0.0f,
        //   0.5f, -0.5f, 0.0f,
        //   0.0f, 0.5f, 0.0f};
        // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        // glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      }
    });

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  t.join();
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(800, 600, "x", nullptr, nullptr);
  if (window == nullptr) {
    std::cerr << "no window\n";
    return 1;
  }

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

  initImgui(window);

  // ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  renderLoop(window);

  cleanUp(window);
  return 0;
}
