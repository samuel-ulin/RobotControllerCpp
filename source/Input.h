#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include <GLFW/glfw3.h>

#include "State.h"

class Input
{
public:
    Input(State& state);

    static std::vector<std::string> getAvailableJoysticks();

    void updateJoystick();

    void setController(std::string name);
    void setController(int id);

private:

    void stateCallback(State::ControllerUpdateType type);

    State &m_state;

    int m_controllerIdx;
};
