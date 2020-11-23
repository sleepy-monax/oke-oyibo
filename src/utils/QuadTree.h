#pragma once

#include "utils/Callback.h"
#include "utils/Common.h"
#include "utils/OwnPtr.h"
#include "utils/Rect.h"
#include "utils/Vector.h"

namespace utils
{
    template <typename TScalar, typename TData>
    class QuadTree
    {
    private:
        static constexpr size_t CAPACITY = 16;

        using DataIterationCallback =
            Callback<Iteration(const Vec2<TScalar> &, const TData &data)>;

        using StructIterationCallback =
            Callback<Iteration(const Rect<TScalar> &bound)>;

        struct Element
        {
            Vec2<TScalar> position;
            TData data;
        };

        class Node
        {
        private:
            bool _sub_divided = false;
            Rect<TScalar> _bound;

            OwnPtr<Node> _top_left;
            OwnPtr<Node> _bottom_left;
            OwnPtr<Node> _top_right;
            OwnPtr<Node> _bottom_right;

            Vector<Element> _elements{};

        public:
            Node(Rect<TScalar> bound) :
                _bound(bound)
            {
            }

            void subdivide()
            {
                if (_sub_divided)
                {
                    return;
                }

                auto top = _bound.take_top();
                auto bottom = _bound.take_bottom();

                _top_left = own<Node>(top.take_left());
                _bottom_left = own<Node>(bottom.take_left());
                _top_right = own<Node>(top.take_right());
                _bottom_right = own<Node>(bottom.take_right());

                _sub_divided = true;

                for (size_t i = 0; i < _elements.count(); i++)
                {
                    auto &el = _elements[i];
                    append(el.position, el.data);
                }

                _elements.clear();
            }

            void append(Vec2<TScalar> position, TData &data)
            {
                if (!_bound.contains(position))
                {
                    return;
                }

                if (_elements.count() + 1 > CAPACITY)
                {
                    subdivide();
                }

                if (_sub_divided)
                {
                    _top_left->append(position, data);
                    _bottom_left->append(position, data);
                    _top_right->append(position, data);
                    _bottom_right->append(position, data);
                }
                else
                {
                    _elements.push_back({position, data});
                }
            }

            Iteration query_elements(Rect<TScalar> bound, DataIterationCallback &callback)
            {
                if (!_bound.colide_with(bound))
                {
                    return Iteration::CONTINUE;
                }

                if (_sub_divided)
                {
                    if (_top_left->query_elements(bound, callback) == Iteration::STOP)
                    {
                        return Iteration::STOP;
                    }

                    if (_bottom_left->query_elements(bound, callback) == Iteration::STOP)
                    {
                        return Iteration::STOP;
                    }

                    if (_top_right->query_elements(bound, callback) == Iteration::STOP)
                    {
                        return Iteration::STOP;
                    }

                    if (_bottom_right->query_elements(bound, callback) == Iteration::STOP)
                    {
                        return Iteration::STOP;
                    }

                    return Iteration::CONTINUE;
                }

                return _elements.foreach ([&](auto &element) {
                    return callback(element.position, element.data);
                });
            }

            Iteration query_structure(Rect<TScalar> bound, StructIterationCallback &callback)
            {
                if (!_bound.colide_with(bound))
                {
                    return Iteration::CONTINUE;
                }

                if (_sub_divided)
                {
                    if (_top_left->query_structure(bound, callback) == Iteration::STOP)
                    {
                        return Iteration::STOP;
                    }

                    if (_bottom_left->query_structure(bound, callback) == Iteration::STOP)
                    {
                        return Iteration::STOP;
                    }

                    if (_top_right->query_structure(bound, callback) == Iteration::STOP)
                    {
                        return Iteration::STOP;
                    }

                    if (_bottom_right->query_structure(bound, callback) == Iteration::STOP)
                    {
                        return Iteration::STOP;
                    }

                    return Iteration::CONTINUE;
                }

                return callback(_bound);
            }
        };

        OwnPtr<Node> _root;
        Rect<TScalar> _bound;

    public:
        QuadTree(Rect<TScalar> bound) :
            _root(own<Node>(bound)), _bound(bound)
        {
        }

        void clear()
        {
            _root = own<Node>(_bound);
        }

        void clear_and_resize(Rect<TScalar> bound)
        {
            _bound = bound;
            clear();
        }

        void append(Vec2<TScalar> position, TData &data)
        {
            _root->append(position, data);
        }

        Iteration query_elements(Rect<TScalar> bound, DataIterationCallback callback)
        {
            return _root->query_elements(bound, callback);
        }

        Iteration query_structure(StructIterationCallback callback)
        {
            return _root->query_structure(_bound, callback);
        }

        Iteration query_structure(Rect<TScalar> bound, StructIterationCallback callback)
        {
            return _root->query_structure(bound, callback);
        }
    };
} // namespace utils
