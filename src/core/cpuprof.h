#pragma once

#undef APIENTRY
#include <windows.h>
#include <iostream>
#include <psapi.h>


unsigned long getMemoryUsageInMB() {
    PROCESS_MEMORY_COUNTERS memoryCounters;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memoryCounters, sizeof(memoryCounters))) {
        // `WorkingSetSize` is in bytes, divide by (1024 * 1024) to convert to MB
        return static_cast<unsigned long>(memoryCounters.WorkingSetSize) / (1024 * 1024);
    } else {
        std::cerr << "Error retrieving memory usage" << std::endl;
        return 0;
    }
}
