#pragma once

#ifdef DEBUG_ALL
    //enable all degging aids
    #define DEBUG_LOGGING
#endif

#ifdef DEBUG_LOGGING
    #include <iostream>
    #define LOG_ERROR(x) std::cerr << "[ERROR] " << #x << std::endl;
    #define LOG(x) std::cout << "[DEBUG] " << #x << std::endl;
#else
    #define LOG_ERROR(X)
    #define LOG(x)
#endif
