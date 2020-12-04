#pragma once

#include "core/Builder.h"
#include "utils/Callback.h"
#include "utils/RefPtr.h"

namespace core
{

    class Blueprint: public utils::RefCounted<Blueprint>
    {
    private:
        utils::Callback<void(Builder &)> _callback{};

    public:
        Blueprint()
        {
        }

        Blueprint(utils::Callback<void(Builder &)> callback) :
            _callback(callback)
        {
        }

        void create(Builder &builder)
        {
            if (_callback)
            {
                _callback(builder);
            }
        }
    };
} // namespace core
