#pragma once

#include <string>

#include "game/RenderContext.h"
#include "input/Controller.h"
#include "utils/OwnPtr.h"

namespace game
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
} // namespace game
