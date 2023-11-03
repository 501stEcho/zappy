/*
** EPITECH PROJECT, 2023
** Entity
** File description:
** zappy
*/

#include "Renderer/Entity.hpp"
#include <raylib.h>

zappy::Entity::Entity(const std::string path)
{
    _model = LoadModel(path.c_str());
    _modelstate = LOADED;
}

zappy::Entity::Entity(const Mesh mesh)
{
    _model = LoadModelFromMesh(mesh);
    _modelstate = LOADED;
}

void zappy::Entity::loadModel(const std::string path)
{
    unloadModel();
    _model = LoadModel(path.c_str());
    _modelstate = LOADED;
}

void zappy::Entity::unloadModel(void)
{
    if (_modelstate == LOADED)
        UnloadModel(_model);
    _shaderlocs.clear();
    _shaderstate = EMPTY;
    _modelstate = EMPTY;
}

void zappy::Entity::loadShader(Shader shader)
{
    _model.materials[0].shader = shader;
    _shaderstate = LOADED;

    _model.materials[0].shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(_model.materials[0].shader, "viewpos");
    _shaderlocs["ambient"] = GetShaderLocation(_model.materials[0].shader, "ambient");
}

void zappy::Entity::updateLight(Light &light)
{
    if (_shaderstate == EMPTY || _modelstate == EMPTY)
        return;
    UpdateLightValues(_model.materials[0].shader, light);
}

Mesh *zappy::Entity::getMesh(void)
{
    if (_modelstate == EMPTY)
        throw EntityException("No model loaded");
    return (_model.meshes);
}

int zappy::Entity::getMeshCount(void)
{
    if (_modelstate == EMPTY)
        throw EntityException("No model loaded");
    return (_model.meshCount);
}

Matrix zappy::Entity::getTransform(void)
{
    if (_modelstate == EMPTY)
        throw EntityException("No model loaded");
    return (_model.transform);
}

void zappy::Entity::updateCameraPosition(Vec3<float> cameraPos)
{
    if (_modelstate == EMPTY)
        throw EntityException("No model loaded");
    if (_shaderstate == EMPTY)
        throw EntityException("No shader loaded");
    float pos[3] = { cameraPos.x, cameraPos.y, cameraPos.z };
    SetShaderValue(_model.materials[0].shader, _model.materials[0].shader.locs[SHADER_LOC_VECTOR_VIEW], pos, SHADER_UNIFORM_VEC3);
}

void zappy::Entity::updateAmbientLight(Vec4<float> ambientLight)
{
    if (_modelstate == EMPTY)
        throw EntityException("No model loaded");
    if (_shaderstate == EMPTY)
        throw EntityException("No shader loaded");
    float ambc[4] = { ambientLight.x, ambientLight.y, ambientLight.z, ambientLight.w };
    SetShaderValue(_model.materials[0].shader, _shaderlocs["ambient"], ambc, SHADER_UNIFORM_VEC4);
}

void zappy::Entity::updatePose(ModelAnimation animation, unsigned int frame)
{
    UpdateModelAnimation(_model, animation, frame % animation.frameCount);
}

void zappy::Entity::addLocation(const std::string locationName)
{
    if (_modelstate == EMPTY)
        throw EntityException("No model loaded");
    if (_shaderstate == EMPTY)
        throw EntityException("No shader loaded");
    if (_shaderlocs.find(locationName) != _shaderlocs.end())
        throw EntityException(locationName + " : Location already existing");
    _shaderlocs[locationName] = GetShaderLocation(_model.materials[0].shader, locationName.c_str());
}
