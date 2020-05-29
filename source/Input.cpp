#include "Input.h"

#include <iostream>

Input::Input(State &state)
    : m_state(state), m_controllerIdx(-1)
{
    state.registerControllerStateCallback(std::bind(&Input::stateCallback, this, std::placeholders::_1));
}

std::vector<std::string> Input::getAvailableJoysticks()
{
    std::vector<std::string> joystickNames{};
    for (size_t i = GLFW_JOYSTICK_1; i <= GLFW_JOYSTICK_LAST; i++) {
        if (glfwJoystickIsGamepad(i)) {
            joystickNames.push_back(glfwGetGamepadName(i));
        }
    }

    return joystickNames;
}

void Input::updateJoystick()
{
    if (m_controllerIdx < 0)
        return;

    GLFWgamepadstate state;

    if (glfwGetGamepadState(m_controllerIdx, &state))
    {

    }
}

void Input::setController(std::string name)
{
    for (size_t i = GLFW_JOYSTICK_1; i <= GLFW_JOYSTICK_LAST; i++) {
        if (glfwJoystickIsGamepad(i)) {
            setController(i);
            return;
        }
    }
}

void Input::setController(int id)
{
    m_controllerIdx = id;
}

void Input::stateCallback(State::ControllerUpdateType type)
{
    std::cout << "Callback called!" << std::endl;
    switch (type) {
    case State::ControllerUpdateType::NAME:
        setController(m_state.getControllerName());
        break;

    default:
        break;
    }
}