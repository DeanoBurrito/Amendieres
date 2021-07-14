#pragma once

#ifdef DEBUG_ALL
    //enable all degging aids
    #define DEBUG_LOGGING
    #define DEBUG_RETURNS
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
    #define LOG_WHERE __FILE__ << ", func=" << __FUNCTION__ << ", line=" << __LINE__
#else
    #define LOG_ERROR(X)
    #define LOG(x)
#endif

#ifdef DEBUG_RETURNS
    #define DEBUG_RETURN_IF(check, msg) if (check) { LOG_ERROR(msg); return; }
    #define DEBUG_RETURN_VAL_IF(check, msg, val) if (check) { LOG_ERROR(msg); return val; }
#else
    #define DEBUG_RETURN_IF(check, msg)
    #define DEBUG_RETURN_VAL_IF(check, msg, val)
#endif
