#pragma once

#define DYNAMIC_ASSERT(cond, message)                            \
    if (not(cond)) {                                             \
        std::cout << "[DYNAMIC_ASSERT]" << message << std::endl; \
        exit(0);                                                 \
    }