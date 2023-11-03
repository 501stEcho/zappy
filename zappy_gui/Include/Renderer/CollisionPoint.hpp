/*
** EPITECH PROJECT, 2023
** Collision
** File description:
** zappy
*/

#pragma once

#include "include.hpp"

namespace zappy
{

    class CollisionPoint {
        public:
            CollisionPoint();
            CollisionPoint(bool hit, float distance, Vec3<float> point, Vec3<float> normal);
            ~CollisionPoint() = default;
            bool hit() const;
            void setHit(bool value);
            float distance() const;
            Vec3<float> point() const;
            Vec3<float> normal() const;

        private:
            bool _hit;
            float _distance;
            Vec3<float> _point;
            Vec3<float> _normal;
    };

}
