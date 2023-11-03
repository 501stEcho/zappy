/*
** EPITECH PROJECT, 2023
** Collision
** File description:
** zappy
*/

#include "Renderer/CollisionPoint.hpp"

zappy::CollisionPoint::CollisionPoint()
{
    _hit = false;
}

zappy::CollisionPoint::CollisionPoint(bool hit, float distance, Vec3<float> point, Vec3<float> normal)
    : _hit(hit), _distance(distance), _point(point), _normal(normal)
{
}

bool zappy::CollisionPoint::hit() const
{
    return (_hit);
}

void zappy::CollisionPoint::setHit(bool value)
{
    _hit = value;
}

float zappy::CollisionPoint::distance() const
{
    return (_distance);
}

zappy::Vec3<float> zappy::CollisionPoint::point() const
{
    return (_point);
}

zappy::Vec3<float> zappy::CollisionPoint::normal() const
{
    return (_normal);
}
