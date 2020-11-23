#pragma once

#include <string>

#include "core/Camera.h"
#include "core/input/Controller.h"
#include "utils/OwnPtr.h"

#include "game/components/Health.h"

namespace core
{
    class Player
    {
    private:
        std::string _name;

        utils::OwnPtr<input::Controller> _controller = nullptr;
        core::Camera _camera{};

    public:
        std::string name() { return _name; }

        input::Controller &controller() { return *_controller; }
        core::Camera &camera() { return _camera; }

        Player(std::string name, utils::OwnPtr<input::Controller> controller) :
            _name(name), _controller(controller)
        {
        }
    };
} // namespace core
