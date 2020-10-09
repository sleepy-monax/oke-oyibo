#pragma once

namespace utils
{
    template <typename T>
    class RefCounted
    {
    private:
        int _refcount;
        bool _orphan;

        __noncopyable(RefCounted);
        __nonmovable(RefCounted);

    public:
        RefCounted()
        {
            _refcount = 1;
            _orphan = false;
        }

        virtual ~RefCounted()
        {
            if (!_orphan)
            {
                assert(_refcount == 0);
            }
        }

        // FIXME: Find a better name for this...
        void make_orphan()
        {
            _orphan = true;
        }

        void ref()
        {
            if (!_orphan)
            {
                assert(_refcount > 0);

                _refcount++;
            }
        }

        void deref()
        {
            if (!_orphan)
            {
                assert(_refcount > 0);

                _refcount--;

                if (_refcount == 1)
                {
                    if constexpr (requires(const T &t) {
                                      t.one_ref_left();
                                  })
                    {
                        this->one_ref_left();
                    }
                }

                if (_refcount == 0)
                {
                    delete static_cast<T *>(this);
                }
            }
        }

        int refcount()
        {
            if (!_orphan)
            {
                return _refcount;
            }
            else
            {
                return 0;
            }
        }
    };
} // namespace utils