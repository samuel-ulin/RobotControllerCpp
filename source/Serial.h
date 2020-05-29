#ifndef SERIAL_H
#define SERIAL_H

#ifdef _WIN32

#include <Windows.h>

#endif

#ifdef __linux__

#endif

#include <stdexcept>
#include <string>
#include <vector>

class Serial
{
public:
    enum class Baudrate {
        B_110,
        B_300,
        B_600,
        B_1200,
        B_2400,
        B_4800,
        B_9600,
        B_19200,
        B_38400,
        B_57600,
        B_115200,
        B_128000,
        B_256000
    };

    Serial(std::string deviceName, Baudrate rate);

    static std::vector<std::string> enumeratePorts();

    bool open();

    bool close();

    size_t writeBytes(const char* buffer, size_t len);

    size_t readBytes(char* buffer, size_t len);

    bool waitEvent();

    Baudrate getBaudrate();

    void setBaudrate(Baudrate rate);

    std::string getDeviceName();



private:
    Baudrate m_rate;

    std::string m_deviceName;

#ifdef _WIN32
    HANDLE m_COMHandle;
#endif

#ifdef __linux__
    int m_serialFile;
#endif
};

static int baudrateToInt(Serial::Baudrate rate)
{
    switch (rate) {
    case Serial::Baudrate::B_110:
        return 110;
        break;
    case Serial::Baudrate::B_300:
        return 300;
        break;
    case Serial::Baudrate::B_600:
        return 600;
        break;
    case Serial::Baudrate::B_1200:
        return 1200;
        break;
    case Serial::Baudrate::B_2400:
        return 2400;
        break;
    case Serial::Baudrate::B_4800:
        return 4800;
        break;
    case Serial::Baudrate::B_9600:
        return 9600;
        break;
    case Serial::Baudrate::B_19200:
        return 19200;
        break;
    case Serial::Baudrate::B_38400:
        return 38400;
        break;
    case Serial::Baudrate::B_57600:
        return 57600;
        break;
    case Serial::Baudrate::B_115200:
        return 115200;
        break;
    case Serial::Baudrate::B_128000:
        return 128000;
        break;
    case Serial::Baudrate::B_256000:
        return 256000;
        break;
    default:
        break;
    }

    return 0;
}

static std::string baudrateToString(Serial::Baudrate rate)
{
    return std::to_string(baudrateToInt(rate));
}

#endif // SERIAL_H