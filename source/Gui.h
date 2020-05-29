#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <string>
#include <vector>

#include "Input.h"
#include "State.h"

class Gui {
public:
    Gui(State& state);
    ~Gui();

    bool init();

    void update();

    void drawControllerState();

    GLFWwindow *getWindow();

private:
    State& m_state;

    GLFWwindow *m_window;

    // State
    ImVec4 m_clear_color;

    bool m_init;
};