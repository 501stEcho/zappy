/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ParticlesManager.hpp
*/

#pragma once

#include "GameState/Types/Types.hpp"
#include "Vector.hpp"
#include "raylib.h"
#include <cstddef>
#include <random>

enum ParticleDirection {
    POS,
    NEG,
    DOUBLE
};

class Particle
{
public:
    Particle(std::size_t lifeTime, zappy::Vec3<float> position, zappy::Vec3<float> direction, Color color);
    ~Particle() = default;

    auto move() -> void;
    auto render() -> void;
    auto getLifeTime() const -> std::size_t;

private:
    std::size_t _lifeTime;
    zappy::Vec3<float> _position;
    zappy::Vec3<float> _direction;
    Color _color;
};

class ParticleManager
{
public:
    ParticleManager();
    ~ParticleManager() = default;

    auto addParticles(zappy::Vec3<float> position, std::size_t nbParticles, zappy::Vec3<float> amplitudes, Color color, ParticleDirection dir) -> void;
    auto render() -> void;

private:
    std::vector<std::unique_ptr<Particle>> _playingParticle;
    std::mutex _mutex;
    std::mt19937 _generator;
};