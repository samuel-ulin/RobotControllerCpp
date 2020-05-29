#include <State.h>

State::State()
    : m_controllerName{"None"}
{}

const std::string& State::getControllerName() const
{
    return m_controllerName;
}

void State::setControllerName(std::string name)
{
    onControllerStateUpdate(ControllerUpdateType::NAME);
    m_controllerName = name;
}

void State::registerControllerStateCallback(std::function<void(ControllerUpdateType)> fn)
{
    m_controllerSubscriptions.push_back(fn);
}
void State::registerSerialStateCallback(std::function<void(SerialUpdateType)> fn)
{
    m_serialSubscriptions.push_back(fn);
}

void State::onControllerStateUpdate(ControllerUpdateType type)
{
    for (auto& fn : m_controllerSubscriptions)
    {
        fn(type);
    }
}

void State::onSerialStateUpdate(SerialUpdateType type)
{
    for (auto &fn : m_serialSubscriptions) {
        fn(type);
    }
}