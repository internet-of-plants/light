#ifndef IOP_LIB_SENSORS_LIGHT_HPP
#define IOP_LIB_SENSORS_LIGHT_HPP

#include <relay.hpp>

namespace relay {
enum class State {
    ON,
    OFF,
};

class Light {
    relay::TimedRelay relay;
public:
    Light(const iop_hal::PinRaw pin) noexcept: relay(pin) {}
    Light(relay::Relay relay) noexcept: relay(std::move(relay)) {}
    Light(relay::TimedRelay relay) noexcept: relay(std::move(relay)) {}

    auto setTime(const relay::Moment moment, const State state) noexcept -> void {
        auto data = iop_hal::io::Data::HIGH;
        if (state == State::OFF) data = iop_hal::io::Data::LOW;
        this->relay.setTime(moment, data);
    }

    auto begin() const noexcept -> void {
        this->relay.begin();
    }

    auto actIfNeeded() noexcept -> bool {
        return this->relay.actIfNeeded();
    }

    auto reset() noexcept -> void {
        this->relay.setLow();
        this->relay.clear();
    }

    auto turn(State state) const noexcept -> void {
        auto data = iop_hal::io::Data::HIGH;
        if (state == State::OFF) data = iop_hal::io::Data::LOW;
        this->relay.set(data);
    }
    auto turnOn() const noexcept -> void { this->relay.setHigh(); }
    auto turnOff() const noexcept -> void { this->relay.setLow(); }

    ~Light() noexcept { this->reset(); }
};
}

#endif