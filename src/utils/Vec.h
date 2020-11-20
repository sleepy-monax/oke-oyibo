#pragma once

namespace utils
{
    enum class Dimension
    {
        X,
        Y,
    };

    static inline Dimension dimension_invert_xy(Dimension dimension)
    {
        if (dimension == Dimension::X)
        {
            return Dimension::Y;
        }
        else
        {
            return Dimension::X;
        }
    }

    template <typename Scalar>
    class Vec2
    {
    private:
        Scalar _x;
        Scalar _y;

    public:
        static Vec2 one() { return Vec2(1, 1); }
        static Vec2 oneX() { return Vec2(1, 0); }
        static Vec2 oneY() { return Vec2(0, 1); }
        static Vec2 zero() { return Vec2(0, 0); }

        Scalar x() const { return _x; }
        Scalar y() const { return _y; }

        Vec2 extract_x() const { return Vec2(_x, 0); }
        Vec2 extract_y() const { return Vec2(0, _y); }

        Vec2() : _x(0), _y(0) {}
        Vec2(Scalar v) : _x(v), _y(v) {}
        Vec2(Scalar x, Scalar y) : _x(x), _y(y) {}

        template <typename OtherScalar>
        Vec2(Vec2<OtherScalar> other)
            : _x(static_cast<Scalar>(other.x())),
              _y(static_cast<Scalar>(other.y()))
        {
        }

        Vec2 operator+(const Vec2 &rhs) const
        {
            return Vec2(x() + rhs.x(), y() + rhs.y());
        }

        Vec2 &operator+=(const Vec2 &rhs)
        {
            *this = *this + rhs;
            return *this;
        }

        Vec2 operator-() const
        {
            return Vec2(-x(), -y());
        }

        Vec2 operator-(const Vec2 &rhs) const
        {
            return Vec2(x() - rhs.x(), y() - rhs.y());
        }

        Vec2 &operator-=(const Vec2 &rhs)
        {
            *this = *this - rhs;
            return *this;
        }

        Vec2 operator*(const Vec2 &rhs) const
        {
            return Vec2(x() * rhs.x(), y() * rhs.y());
        }

        template <typename U>
        Vec2 operator*(const Vec2<U> &rhs) const
        {
            return Vec2(x() * rhs.x(), y() * rhs.y());
        }

        template <typename U>
        Vec2 operator*(U rhs) const
        {
            return Vec2(x() * rhs, y() * rhs);
        }

        template <typename U>
        Vec2 operator/(U rhs) const
        {
            return Vec2(x() / rhs, y() / rhs);
        }

        Vec2 &operator*=(const Vec2 &rhs)
        {
            *this = *this * rhs;
            return *this;
        }

        bool operator==(const Vec2 &rhs) const
        {
            return x() == rhs.x() && y() == rhs.y();
        }

        bool operator!=(const Vec2 &rhs) const
        {
            return x() != rhs.x() || y() != rhs.y();
        }

        double distance_to(const Vec2 &other) const
        {
            return sqrt((x() - other.x()) * (x() - other.x()) +
                        (y() - other.y()) * (y() - other.y()));
        }

        Vec2 clamped(const Vec2 &min, const Vec2 &max) const
        {
            Scalar xx = MAX(min.x(), MIN(max.x(), x()));
            Scalar yy = MAX(min.y(), MIN(max.y(), y()));

            return Vec2(xx, yy);
        }

        Scalar component(Dimension dim)
        {
            if (dim == Dimension::X)
                return x();

            if (dim == Dimension::Y)
                return y();

            assert_not_reached();
        }

        Scalar with_component(Dimension dim, Scalar value)
        {
            if (dim == Dimension::X)
                return Vec2i(value, y());

            if (dim == Dimension::Y)
                return Vec2i(x(), value);

            assert_not_reached();
        }
    };

    using Vec2i = Vec2<int>;
    using Vec2f = Vec2<float>;

} // namespace utils