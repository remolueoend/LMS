#ifndef LMS_EscapeException_h
#define LMS_EscapeException_h


#include <exception>
#include <stdexcept>

class EscapeException : public std::runtime_error {

public:
    EscapeException() : runtime_error("ESCAPE_DETECTED") {}
};



#endif
