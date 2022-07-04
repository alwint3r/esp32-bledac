#ifndef DAC_HPP_
#define DAC_HPP_

#include <stdint.h>
#include <string>


class DAC
{
public:
    DAC(uint8_t digitalData) : digitalData_(digitalData)
    {
    }

    void from(std::string string)
    {
        digitalData_ = static_cast<uint8_t>(std::atoi(string.c_str()));
    }

    void from(uint8_t data)
    {
        digitalData_ = data;
    }

    uint8_t getData()
    {
        return digitalData_;
    }

    std::string toString()
    {
        return std::to_string(digitalData_);
    }

    uint16_t asMillivolt()
    {
        return (digitalData_ * MAX_MILLIVOLT_RANGE) / UINT8_MAX;
    }

    std::string asMillivoltString()
    {
        return std::to_string(asMillivolt());
    }

private:
    static constexpr auto MAX_MILLIVOLT_RANGE = 3300;
    uint8_t digitalData_;
};

#endif