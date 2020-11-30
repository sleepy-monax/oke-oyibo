#pragma once

#include "utils/Macros.h"
#include "utils/Vec.h"

namespace utils
{
    template <typename TScalar>
    struct __packed Rect
    {
    private:
        TScalar _x;
        TScalar _y;
        TScalar _width;
        TScalar _height;

    public:
        static Rect empty()
        {
            return Rect(0, 0, 0, 0);
        }

        static Rect from_two_point(Vec2<TScalar> a, Vec2<TScalar> b)
        {
            auto x0 = MIN(a.x(), b.x());
            auto y0 = MIN(a.y(), b.y());
            auto x1 = MAX(a.x(), b.x());
            auto y1 = MAX(a.y(), b.y());

            return {x0, y0, x1 - x0, y1 - y0};
        }

        auto x() const { return _x; }

        auto y() const { return _y; }

        auto width() const { return _width; }

        auto height() const { return _height; }

        Vec2<TScalar> position() const { return {_x, _y}; }

        Vec2<TScalar> size() const { return {_width, _height}; }

        Vec2<TScalar> top_left() const
        {
            return position();
        }

        Vec2<TScalar> bottom_left() const
        {
            return position() + size().extract_y();
        }

        Vec2<TScalar> top_right() const
        {
            return position() + size().extract_x();
        }

        Vec2<TScalar> bottom_right() const
        {
            return position() + size();
        }

        Vec2<TScalar> top_center() const
        {
            return position() + size().extract_x() / 2;
        }

        Vec2<TScalar> bottom_center() const
        {
            return position() + size().extract_y() + size().extract_x() / 2;
        }

        TScalar top() const
        {
            return y();
        }

        TScalar bottom() const
        {
            return y() + height();
        }

        TScalar left() const
        {
            return x();
        }

        TScalar right() const
        {
            return x() + width();
        }

        TScalar area() { return width() * height(); }

        bool is_empty() const { return _width == 0 || _height == 0; };

        Rect() = default;

        Rect(TScalar width, TScalar height) :
            _x(0),
            _y(0),
            _width(width),
            _height(height)
        {
        }

        Rect(Vec2<TScalar> size) :
            _x(0),
            _y(0),
            _width(size.x()),
            _height(size.y())
        {
        }

        Rect(Vec2<TScalar> position, Vec2<TScalar> size) :
            _x(position.x()),
            _y(position.y()),
            _width(size.x()),
            _height(size.y())
        {
        }

        template <typename TOtherScalar>
        Rect(const Rect<TOtherScalar> &other) :
            _x(other.x()),
            _y(other.y()),
            _width(other.width()),
            _height(other.height())
        {
        }

        Rect(TScalar x, TScalar y, TScalar width, TScalar height) :
            _x(x),
            _y(y),
            _width(width),
            _height(height)
        {
        }

        Rect with_width(TScalar width) const
        {
            Rect new_rect = Rect(*this);
            new_rect._width = width;
            return new_rect;
        }

        Rect with_height(TScalar height) const
        {
            Rect new_rect = Rect(*this);
            new_rect._height = height;
            return new_rect;
        }

        Rect centered_within(Rect container) const
        {
            return Rect(
                container._x + container._width - container._width / 2 - _width / 2,
                container._y + container._height - container._height / 2 - _height / 2,
                _width,
                _height);
        }

        Rect merged_with(Rect other) const
        {
            Vec2<TScalar> topleft(
                MIN(_x, other._x),
                MIN(_y, other._y));

            Vec2<TScalar> bottomright(
                MAX(_x + _width, other._x + other._width),
                MAX(_y + _height, other._y + other._height));

            return Rect::from_two_point(topleft, bottomright);
        }

        Rect clipped_with(Rect other) const
        {
            Vec2<TScalar> topleft(
                MAX(_x, other._x),
                MAX(_y, other._y));

            Vec2<TScalar> bottomright(
                MIN(_x + _width, other._x + other._width),
                MIN(_y + _height, other._y + other._height));

            return Rect::from_two_point(topleft, bottomright);
        }

        Rect take_top() const { return take_top(_height / 2); }
        Rect take_bottom() const { return take_bottom(_height / 2); }
        Rect take_left() const { return take_left(_width / 2); }
        Rect take_right() const { return take_right(_width / 2); }

        Rect take_top_percent(double v) const { return take_top((TScalar)(v * width())); }
        Rect take_top(TScalar size) const
        {
            return Rect(x(), y(), width(), size);
        }

        Rect take_bottom_percent(double v) const { return take_bottom((TScalar)(v * width())); }
        Rect take_bottom(TScalar size) const
        {
            return Rect(x(), y() + height() - size, width(), size);
        }

        Rect take_left_percent(double v) const { return take_left((TScalar)(v * width())); }
        Rect take_left(TScalar size) const
        {
            return Rect(x(), y(), size, height());
        }

        Rect take_right_percent(double v) const { return take_right((TScalar)(v * width())); }
        Rect take_right(TScalar size) const
        {
            return Rect(x() + width() - size, y(), size, height());
        }

        Rect cutoff_top(TScalar top) const
        {
            return cutoff_top_and_botton(top, 0);
        }

        Rect cutoff_botton(TScalar bottom) const
        {
            return cutoff_top_and_botton(0, bottom);
        }

        Rect cutoff_top_and_botton(TScalar top, TScalar bottom) const
        {
            return Rect(x(), y() + top, width(), height() - top - bottom);
        }

        Rect cutoff_left(TScalar left) const
        {
            return cutoff_left_and_right(left, 0);
        }

        Rect cutoff_right(TScalar right) const
        {
            return cutoff_left_and_right(0, right);
        }

        Rect cutoff_left_and_right(TScalar left, TScalar right) const
        {
            return Rect(x() + left, y(), width() - left - right, height());
        }

        Rect row(TScalar row_count, TScalar index) const
        {
            return row(row_count, index, 0);
        }

        Rect row(TScalar row_count, TScalar index, TScalar spacing) const
        {
            assert(index >= 0);
            assert(row_count > 0);

            TScalar spacing_height = spacing * row_count - 1;

            TScalar available_height = height() - spacing_height;

            TScalar row_height = available_height / row_count;

            TScalar correction = available_height - (row_height * row_count);

            TScalar current_row_height = row_height;

            if (index < correction)
            {
                current_row_height += 1;
            }

            TScalar current_row_position =
                row_height * index +
                (spacing * index) +
                MIN(index, correction);

            return Rect{
                x(),
                y() + current_row_position,
                width(),
                row_height,
            };
        }

        Rect column(TScalar column_count, TScalar index) const
        {
            return column(column_count, index, 0);
        }

        Rect column(TScalar column_count, TScalar index, TScalar spacing) const
        {
            assert(index >= 0);
            assert(column_count > 0);

            TScalar spacing_width = spacing * column_count - 1;

            TScalar available_width = width() - spacing_width;

            TScalar column_width = available_width / column_count;

            TScalar correction = available_width - (column_width * column_count);

            TScalar current_column_width = column_width;
            if (index < correction)
            {
                current_column_width += 1;
            }

            TScalar current_column_position =
                column_width * index +
                (spacing * index) +
                MIN(index, correction);

            return Rect{
                x() + current_column_position,
                y(),
                current_column_width,
                height(),
            };
        }

        Rect shrinked(TScalar gaps) const
        {
            assert(gaps >= 0);

            return Rect(
                _x + gaps,
                _y + gaps,
                MAX(0, _width - gaps - gaps),
                MAX(0, _height - gaps - gaps));
        }

        Rect shrinked(Vec2<TScalar> gaps) const
        {
            return Rect(
                _x + gaps.x(),
                _y + gaps.y(),
                MAX(0, _width - gaps.x() - gaps.x()),
                MAX(0, _height - gaps.y() - gaps.y()));
        }

        Rect expended(TScalar gaps) const
        {
            assert(gaps >= 0);

            return Rect(
                _x - gaps,
                _y - gaps,
                _width + gaps + gaps,
                _height + gaps + gaps);
        }

        Rect resized(Vec2<TScalar> size) const
        {
            return Rect(
                _x,
                _y,
                size.x(),
                size.y());
        }

        Rect moved(Vec2<TScalar> position) const
        {
            return Rect(position, size());
        }

        Rect offset(Vec2<TScalar> offset) const
        {
            return Rect(position() + offset, size());
        }

        bool colide_with(Rect other) const
        {
            return _x < other._x + other._width &&
                   _x + _width > other._x &&
                   _y < other._y + other._height &&
                   _height + _y > other._y;
        }

        bool contains(Vec2<TScalar> other) const
        {
            return (_x <= other.x() && (_x + _width) > other.x()) &&
                   (_y <= other.y() && (_y + _height) > other.y());
        }

        bool contains(Rect other) const
        {
            return (_x <= other._x && (_x + _width) >= (other._x + other._width)) &&
                   (_y <= other._y && (_y + _height) >= (other._y + other._width));
        }

        void substract(Rect other, Rect &t, Rect &b, Rect &l, Rect &r) const
        {
            if (colide_with(other))
            {
                other = other.clipped_with(*this);

                l = Rect(x(), y(), other.left() - left(), height());
                r = Rect(other.right(), y(), right() - other.right(), height());

                t = Rect(l.right(), y(), r.left() - l.right(), other.top() - top());
                b = Rect(l.right(), other.bottom(), r.left() - l.right(), bottom() - other.bottom());
            }
            else
            {
                t = *this;
                b = empty();
                l = empty();
                r = empty();
            }
        }
    };

    using Recti = Rect<int>;
    using Rectf = Rect<float>;

} // namespace utils