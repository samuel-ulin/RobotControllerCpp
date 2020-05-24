#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <numeric>
#include <string>

#include "Serial.h"

void serialPerformanceTest(const int samples)
{
    auto ports = Serial::enumeratePorts();

    Serial serialDevice{ ports.front(), Serial::Baudrate::B_9600 };

    if (!serialDevice.open())
        std::cerr << "Couldn't open serial file" << std::endl;

    std::vector<double> timePoints(samples, 0.0);

    auto t0 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < samples; i++) {
        std::string msg{ "abcdabcdabcdabcd" };
        if (msg.compare("quit") == 0)
            break;

        msg.push_back('\n');

        if (!serialDevice.writeBytes(msg.data(), msg.length()))
            std::cerr << "Couldn't write bytes to serial file" << std::endl;

        if (serialDevice.waitEvent()) {
            std::string buffer;
            buffer.resize(1024);
            size_t len = serialDevice.readBytes(buffer.data(), 1 << 10);
        }

        timePoints[i] = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t0).count();
    }

    serialDevice.close();

    std::vector<double> times(timePoints.size(), 0.0);
    std::adjacent_difference(timePoints.begin(), timePoints.end(), times.begin());

    double total = timePoints.back();
    double mean = total / samples;
    auto squareDistanceAccumulator = [&mean](auto lhs, auto rhs) { return lhs + (mean - rhs) * (mean - rhs); };
    double stddev = std::sqrt(std::reduce(std::execution::par, times.begin(), times.end(), 0.0, squareDistanceAccumulator) / static_cast<double>(samples - 1));

    std::cout << "Took:    " << total << " seconds" << std::endl;
    std::cout << "Average: " << mean << " seconds " << std::endl;
    std::cout << "Stddev:  " << stddev << " seconds" << std::endl;
}

int main(int argc, char **argv)
{
    

    return 0;
}