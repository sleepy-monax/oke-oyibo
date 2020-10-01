#pragma once

#include <string>

#include "core/game/RenderContext.h"
#include "core/input/Controller.h"
#include "utils/OwnPtr.h"

namespace core::game
{
    class Player
    {
    private:
        std::string _name;
        utils::OwnPtr<input::Controller> _controller = nullptr;
        RenderContext _render{};

    public:
        input::Controller &controller() { return *_controller; }
        RenderContext &render() { return _render; }

        Player(std::string name, utils::OwnPtr<input::Controller> controller)
            : _name(name), _controller(controller)
        {
        }
    };
} // namespace core::game
