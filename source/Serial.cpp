#include "Serial.h"

#include <algorithm>
#include <iostream>

Serial::Serial(std::string deviceName, Baudrate rate)
    : m_rate(rate), m_COMHandle(NULL)
{
    auto ports = enumeratePorts();
    auto it = std::find_if(
        ports.begin(), ports.end(), [&deviceName](const auto &s) { return deviceName.compare(s) == 0; });

    if (it == ports.end())
        throw std::runtime_error{ "No serial device exists with given name" };

    m_deviceName = deviceName;
}

std::vector<std::string> Serial::enumeratePorts()
{
    // Return vec
    std::vector<std::string> ports{};

#ifdef _WIN32
    // Allocate buffer to store query string
    std::vector<char> buffer;
    buffer.resize(1 << 14);

    // Make sure error is cleared and attempt to query devices
    SetLastError(NO_ERROR);
    QueryDosDeviceA(NULL, buffer.data(), buffer.size());

    // If insufficient buffer size, double the size and retry
    while (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
        if (buffer.size() >= 1 << 20) {
            throw std::runtime_error{ "QueryDosDeviceA buffer exceeded 1MiB" };
        }
        buffer.resize(buffer.size() * 2);

        SetLastError(NO_ERROR);
        QueryDosDeviceA(NULL, buffer.data(), buffer.size());
    }

    for (char *pBegin = buffer.data(); *pBegin != '\0'; pBegin++) {
        char *pEnd;
        for (pEnd = pBegin; *pEnd != '\0'; pEnd++)
            ;

        std::string device{ pBegin, pEnd };
        if (device.compare(0, 3, "COM") == 0) {
            ports.push_back(device);
        }
        pBegin = pEnd;
    }
#endif// _WIN32

#ifdef __linux__

#endif// __linux__

    return ports;
}

bool Serial::open()
{
#ifdef _WIN32

    DCB dcb;
    COMMTIMEOUTS timeouts;

    if (m_COMHandle && !close())
        return false;

    m_COMHandle = CreateFileA(m_deviceName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (m_COMHandle == INVALID_HANDLE_VALUE) {
        m_COMHandle = NULL;
        return false;
    }

    if (!SetupComm(m_COMHandle, 64, 64)) {
        close();
        return false;
    }

    if (!GetCommState(m_COMHandle, &dcb)) {
        close();
        return false;
    }

    dcb.BaudRate = baudrateToInt(m_rate);
    dcb.fBinary = 1;
    dcb.fParity = 0;
    dcb.fErrorChar = 0;
    dcb.fNull = 0;
    dcb.fAbortOnError = 0;
    dcb.ByteSize = 8;
    dcb.StopBits = 0;
    dcb.EvtChar = '\n';

    if (!SetCommState(m_COMHandle, &dcb)) {
        close();
        return false;
    }

    timeouts.ReadIntervalTimeout = MAXDWORD;
    timeouts.ReadTotalTimeoutConstant = 0;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    timeouts.WriteTotalTimeoutConstant = 0;
    timeouts.WriteTotalTimeoutMultiplier = 0;

    if (!SetCommTimeouts(m_COMHandle, &timeouts)) {
        close();
        return false;
    }

    if (!SetCommMask(m_COMHandle, EV_RXCHAR | EV_ERR)) {
        close();
        return false;
    }
#endif// _WIN32


    return true;
}

bool Serial::close()
{
#ifdef _WIN32
    if (m_COMHandle)
        return CloseHandle(m_COMHandle);
#endif// _WIN32

#ifdef __linux__

#endif// __linux__
    return true;
}

size_t Serial::writeBytes(const char *buffer, size_t len)
{
#ifdef _WIN32
    if (m_COMHandle) {
        DWORD bytes;
        if (WriteFile(m_COMHandle, buffer, len, &bytes, NULL)) {
            return bytes;
        }
    }
#endif// _WIN32


    return 0;
}

size_t Serial::readBytes(char *buffer, size_t len)
{
#ifdef _WIN32
    if (m_COMHandle) {
        DWORD bytes;
        if (ReadFile(m_COMHandle, buffer, len, &bytes, NULL)) {
            return bytes;
        }
    }
#endif// _WIN32

#ifdef __linux__

#endif// __linux__
    return 0;
}

bool Serial::waitEvent()
{
    if (m_COMHandle) {
        DWORD eventMask = 0;
        SetCommMask(m_COMHandle, EV_RXFLAG | EV_ERR);
        WaitCommEvent(m_COMHandle, &eventMask, 0);
        if (eventMask & EV_RXFLAG)
            return true;
    }
    return false;
}

Serial::Baudrate Serial::getBaudrate()
{
    return m_rate;
}

void Serial::setBaudrate(Baudrate rate)
{
    m_rate = rate;
}

std::string Serial::getDeviceName()
{
    return m_deviceName;
}