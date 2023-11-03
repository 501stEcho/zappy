/*
** EPITECH PROJECT, 2023
** Entity
** File description:
** zappy
*/

#pragma once

#include "include.hpp"

namespace zappy
{
    enum LoadState
    {
        LOADED,
        EMPTY
    };

    class EntityException : public std::exception {
        public:
            explicit EntityException(std::string reason) : _reason(std::move(reason))
            {};

            [[nodiscard]] const char *what() const noexcept override
            {
                return _reason.c_str();
            };

        private:
            std::string _reason;
    };

    class Entity {
        public:
            Entity(const std::string path);
            Entity(const Mesh mesh);

            void loadModel(const std::string path);
            void unloadModel(void);
            void loadShader(Shader shader);
            void addLocation(const std::string locationName);
            void updateLight(Light &light);
            Mesh *getMesh(void);
            int getMeshCount(void);
            Matrix getTransform(void);
            void updateCameraPosition(Vec3<float> cameraPos);
            void updateAmbientLight(Vec4<float> ambientLight);
            void updatePose(ModelAnimation animation, unsigned int frame);

            template<typename T>
            void setShaderValue(const std::string locationName, T *value, ShaderUniformDataType type)
            {
                if (_modelstate == EMPTY)
                    throw EntityException("No model loaded");
                if (_shaderstate == EMPTY)
                    throw EntityException("No shader loaded");
                if (_shaderlocs.find(locationName) != _shaderlocs.end())
                    SetShaderValue(_model.materials[0].shader, _shaderlocs[locationName], value, type);
                else
                    throw EntityException(locationName + " : Unknown location name");
            }

            ~Entity() = default;

            Model _model;
            LoadState _shaderstate;
            LoadState _modelstate;
            Vector3 _position;
            std::map<std::string, int> _shaderlocs;
            float _scale;
    };

}
