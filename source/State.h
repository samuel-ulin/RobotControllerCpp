#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

class State
{
public:
    enum class ControllerUpdateType
    {
        NAME
    };

    enum class SerialUpdateType
    {
        NAME
    };

    struct ControllerState
    {
        uint16_t buttons;
        uint8_t axes;
    };

    State();
    
    const std::string& getControllerName() const;
    void setControllerName(std::string name);

    void registerControllerStateCallback(std::function<void(ControllerUpdateType)> fn);
    void registerSerialStateCallback(std::function<void(SerialUpdateType)> fn);

private:
    // Trigger callbacks
    void onControllerStateUpdate(ControllerUpdateType type);
    void onSerialStateUpdate(SerialUpdateType type);
    
    // Subscriptions
    std::vector<std::function<void(ControllerUpdateType)>> m_controllerSubscriptions;
    std::vector<std::function<void(SerialUpdateType)>> m_serialSubscriptions;

    // State variables

    // Controller
    std::string m_controllerName;
    
};