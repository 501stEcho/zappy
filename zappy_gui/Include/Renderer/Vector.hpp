/*
** EPITECH PROJECT, 2023
** Vec3
** File description:
** zappy
*/

#pragma once

namespace zappy
{
    template<typename T>
    struct Vec2 {
            Vec2() = default;
            Vec2(T xx, T yy) : x(xx), y(yy) {};
            ~Vec2() = default;

            T x;
            T y;
    };

    template<typename T>
    struct Vec3 {
            Vec3() = default;
            Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {};
            ~Vec3() = default;

            T x;
            T y;
            T z;
    };

    template<typename T>
    struct Vec4 {
            Vec4() = default;
            Vec4(T xx, T yy, T zz, T ww) : x(xx), y(yy), z(zz), w(ww) {};
            ~Vec4() = default;

            T x;
            T y;
            T z;
            T w;
    };
}
