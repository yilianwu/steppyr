#ifndef __STEPPYR_HPP
#define __STEPPYR_HPP

#include "drivers/drivers.hpp"

class StepperController {
public:
    void activate();
    void shutdown();

    void stop();

private:

};

#endif
