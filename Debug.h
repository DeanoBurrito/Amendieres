#pragma once

#ifdef DEBUG_ALL
    //enable all degging aids
    #define DEBUG_LOGGING
#endif

#ifdef DEBUG_LOGGING
    #include <iostream>

    struct DebugEndlineInserter
    {
        std::ostream& str;
        
        DebugEndlineInserter(std::ostream& stream) : str(stream) {}
        
        ~DebugEndlineInserter()
        {
            str << std::endl;
        }
    };

    #define LOG_ERROR(x) (DebugEndlineInserter(std::cerr), std::cerr << "[ERROR] " << x)
    #define LOG(x) (DebugEndlineInserter(std::cout), std::cout << "[DEBUG] " << x)
#else
    #define LOG_ERROR(X)
    #define LOG(x)
#endif
