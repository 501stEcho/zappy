/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ParticlesManager.cpp
*/

#include "Renderer/ParticlesManager.hpp"
#include "Beans/Bean.hpp"
#include "GameState/Types/Types.hpp"
#include "Renderer/Renderer.hpp"
#include <cstddef>
#include <memory>
#include <raylib.h>

template <typename T>
auto randomFloatingGen(std::mt19937 &generator, const T &min, const T &max) -> T
{
    std::uniform_real_distribution<T> distribution(min, max);
    return distribution(generator);
}

template <typename T>
auto randomIntegerGen(std::mt19937 &generator, const T &min, const T &max) -> T
{
    std::uniform_int_distribution<T> distribution(min, max);
    return distribution(generator);
}

Particle::Particle(std::size_t lifeTime, zappy::Vec3<float> position, zappy::Vec3<float> direction, Color color)
    : _lifeTime(lifeTime), _position(position), _direction(direction), _color(color)
{
}

auto Particle::move() -> void
{
    if (_lifeTime == 0)
        return;
    _position.x += _direction.x;
    _position.y += _direction.y;
    _position.z += _direction.z;
    _lifeTime--;
}

auto Particle::render() -> void
{
    if (_lifeTime == 0)
        return;
    auto &renderer = Bean<zappy::Renderer>::getInstance();
    renderer.drawCube(_position, zappy::Vec3<float>(0.05, 0.05, 0.05), _color);
}

auto Particle::getLifeTime() const -> std::size_t
{
    return _lifeTime;
}

ParticleManager::ParticleManager()
{
}

auto ParticleManager::addParticles(zappy::Vec3<float> position, std::size_t nbParticles, zappy::Vec3<float> amplitudes, Color color, ParticleDirection dir) -> void
{
    std::lock_guard<std::mutex> lock(_mutex);
    for (std::size_t i = 0; i < nbParticles; i++) {
        auto lifeTime = randomIntegerGen(_generator, 10, 50);
        auto direction = zappy::Vec3<float>(
        randomFloatingGen<float>(_generator, dir == POS ? 0 : -amplitudes.x, dir == NEG ? 0 : amplitudes.x),
        randomFloatingGen<float>(_generator, dir == POS ? 0 : -amplitudes.y, dir == NEG ? 0 : amplitudes.y),
        randomFloatingGen<float>(_generator, dir == POS ? 0 : -amplitudes.z, dir == NEG ? 0 : amplitudes.z));
        _playingParticle.push_back(std::make_unique<Particle>(lifeTime, position, direction, color));
    }
}

auto ParticleManager::render() -> void
{
    std::lock_guard<std::mutex> lock(_mutex);
    for (auto &particle : _playingParticle) {
        particle->move();
        particle->render();
    }
    _playingParticle.erase(std::remove_if(_playingParticle.begin(), _playingParticle.end(), [](const auto &particle) {
        return particle->getLifeTime() == 0;
    }),
    _playingParticle.end());
}
