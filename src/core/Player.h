#pragma once

#include <string>

#include "core/Camera.h"
#include "core/Controller.h"
#include "utils/OwnPtr.h"

#include "game/components/Health.h"

namespace core
{
    class Player
    {
    private:
        std::string _name;

        utils::OwnPtr<Controller> _controller = nullptr;
        core::Camera _camera{};

    public:
        std::string name() { return _name; }

        core::Controller &controller() { return *_controller; }
        core::Camera &camera() { return _camera; }

        Player(std::string name, utils::OwnPtr<core::Controller> controller) :
            _name(name), _controller(controller)
        {
        }
    };
} // namespace core
