// ---- memoryhandler.h ----

#ifndef MEMORY_HANDLER_H
#define MEMORY_HANDLER_H

// #include <EEPROM.h>
#include "realay.h"

class MemoryHandeler
{
public:
    // -- Menu features --
    // Style
    // mainSwitch
    // Periods
    // -- Relay --
    static void SaveRelayDataToMemory(const Relay &rel, const uint8_t periodNumber);
    static void LoadRelayDataFromMemory(const Relay &rel, const uint8_t periodNumber);
};

#endif