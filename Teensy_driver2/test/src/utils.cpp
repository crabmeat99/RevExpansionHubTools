
#include <string>
#include "rhsp_time.h"

std::string nackMeanings[] = {
        "Parameter #0 out of range",
        "Parameter #1 out of range",
        "Parameter #2 out of range",
        "Parameter #3 out of range",
        "Parameter #4 out of range",
        "Parameter #5 out of range",
        "Parameter #6 out of range",
        "Parameter #7 out of range",
        "Parameter #8 out of range",
        "Parameter #9 out of range",
        "GPIO #0 not configured for output",
        "GPIO #1 not configured for output",
        "GPIO #2 not configured for output",
        "GPIO #3 not configured for output",
        "GPIO #4 not configured for output",
        "GPIO #5 not configured for output",
        "GPIO #6 not configured for output",
        "GPIO #7 not configured for output",
        "No GPIO pins configured for output",
        "Unused, reserved",
        "GPIO #0 not configured for input",
        "GPIO #1 not configured for input",
        "GPIO #2 not configured for input",
        "GPIO #3 not configured for input",
        "GPIO #4 not configured for input",
        "GPIO #5 not configured for input",
        "GPIO #6 not configured for input",
        "GPIO #7 not configured for input",
        "No GPIO pins configured for input",
        "Unused, reserved",
        "Servo not fully configured before enabled",
        "Battery voltage too low to run servo.",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "I2C Master Busy (command rejected)",
        "I2C Operation in progress (poll again for completion status)",
        "I2C No results pending",
        "I2C Query mismatch (query doesn’t match last operation)",
        "I2C Timeout SDA stuck",
        "I2C Timeout SCK stuck",
        "I2C Timeout",
        "",
        "",
        "",
        "Motor not fully configured for selected mode before enabled",
        "Command not valid for selected motor mode",
        "Battery voltage too low to run motor.",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "Command implementation pending (software diagnostic; command is known and properly delivered but implementation is not complete)",
        "Command routing error (software diagnostic; command is known but not handled by receiving subsystem)",
        "Packet Type ID unknown (protocol failure; no unknown commands should be sent if discovery was performed properly)"
};

void delay(int timeMillis)
{
    uint32_t start = rhsp_getSteadyClockMs();

    while (rhsp_getSteadyClockMs() - start < timeMillis);
}
