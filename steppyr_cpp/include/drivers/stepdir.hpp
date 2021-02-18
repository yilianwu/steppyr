#ifndef __STEPPYR_DRIVERS_STEPDIR_HPP
#define __STEPPYR_DRIVERS_STEPDIR_HPP

#include "drivers/drivers.hpp"

class StepDirDriver : public Driver {
public:
    StepDirDriver(int dir_pin, int step_pin, int enable_pin = 0);
    ~StepDirDriver();

    void activate() override;
    void shutdown() override;
    void enable() override;
    void disable() override;
    void step(Direction direction) override;

private:
    int dir_pin;
    int step_pin;
    int enable_pin;
};

#endif
