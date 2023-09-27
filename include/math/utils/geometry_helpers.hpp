#pragma once

#include <initializer_list>
#include <sstream>
#include <string>
#include <utility>

#include <math/vec3_t.hpp>

namespace math {

template <typename T>
struct Line {
    using Vec3 = ::math::Vector3<T>;

    /// Represents the start point of this line
    Vec3 start;
    /// Represents the end point of this line
    Vec3 end;

    /// \brief Creates a default line with both start and end set to the origin
    Line() = default;

    /// \brief Creates a line with given start and end points
    ///
    /// \param p_start The first|starting point of the line
    /// \param p_end The second/ending point of the line
    Line(Vec3 p_start, Vec3 p_end)
        : start(std::move(p_start)), end(std::move(p_end)) {}

    /// \brief Creates a line from a given initializer list of points
    ///
    /// \param points List of points that define the line (start, end)
    Line(const std::initializer_list<Vec3>& points) {
        assert(points.size() == 2);

        auto it = points.begin();
        start = *it++;
        end = *it;
    }

    /// \brief Returns a string representation of this line
    /// \return The string representation of this line
    auto toString() const -> std::string {
        std::stringstream str_result;
        str_result << "<Line"
                   << "\n";
        str_result << "  start: " << start.toString() << "\n";
        str_result << "  end: " << end.toString() << "\n";
        str_result << ">\n";
        return str_result.str();
    }

    /// \brief Returns the distance from the given point to this line
    ///
    /// \param point The point from which to take the distance
    /// \return The distance from the point to this line
    auto distanceTo(const Vec3& point) const -> T {
        const auto SIDE_A = point - start;
        const auto SIDE_B = point - end;
        const auto SIDE_C = end - start;
        auto cross_ab = SIDE_A.cross(SIDE_B);
        auto len_ab = cross_ab.length();
        auto len_c = SIDE_C.length();
        return len_ab / len_c;
    }
};

}  // namespace math
