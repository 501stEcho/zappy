/*
** EPITECH PROJECT, 2023
** Renderer
** File description:
** zappy
*/

#pragma once

#include "include.hpp"
#include "Entity.hpp"
#include "CollisionPoint.hpp"
#include <raylib.h>

namespace zappy
{

    #define WIN3D_WIDTH 1600
    #define WIN3D_HEIGHT 800

    enum Axis
    {
        X,
        Y,
        Z
    };

    enum KeyBind
    {
        MOUSE_LEFT,
        MOUSE_RIGHT,
        RIGHT,
        DOWN,
        UP,
        LEFT
    };

    class RendererException : public std::exception {
        public:
            explicit RendererException(std::string reason) : _reason(std::move(reason))
            {};

            [[nodiscard]] const char *what() const noexcept override
            {
                return _reason.c_str();
            };

        private:
            std::string _reason;
    };

    class LightSource {
        public:
            LightSource(Light light, bool moving, double radius, Axis axis);
            void adaptPosition(double sunAngle);
            Light &getLight();

        private:
            Light _light;
            Axis _axis;
            bool _moving;
            double _radius;
    };

    class Renderer {
        public:
            Renderer();

            void addShader(const std::string shaderName, const std::string vertexShaderPath, const std::string fragmentShaderPath);
            void addObject(const std::string objName, const std::string objModelPath);
            void addTexture(const std::string textureName, const std::string pathName);

            void setAmbientColors(const std::string pathName);
            void setObjectShader(const std::string objName, const std::string shaderName);
            void setSkybox(const std::string pathName, const std::string vertexShaderPath, const std::string fragmentShaderPath,
                const std::string cubemapVertexShader, const std::string cubemapFragmentShader);

            void actualize(void);

            void enableDrawing(void);
            void disableDrawing(void);
            void enable3DMode(void);
            void disable3DMode(void);
            void enableBlendMode(void);
            void disableBlendMode(void);

            bool keyDown(KeyBind key);
            bool keyUp(KeyBind key);
            bool keyPressed(KeyBind key);
            bool keyReleased(KeyBind key);

            int getWindowWidth(void);
            int getWindowHeight(void);

            void displaySkybox(void);
            void displayLights(void);

            void displayObject(const std::string object, Vec3<float> position, Vec3<float> orientation = Vec3<float>(0, 0, 0));
            void displayTexture(const std::string texture, float scale, Vec2<float> position);
            void displayBillboardTexture(const std::string texture, float size, Vec3<float> position, bool center = false);
            void displayBoundingBox(const std::string object, Vec3<float> position);
            void drawText(const std::string text, Vec2<float> position, int fontSize, Color color);
            void drawTextInImage(const std::string textureName, const std::string msg, Vec3<float> position, float fontSize, Color color);
            void drawCube(Vec3<float> position, Vec3<float> size, Color color);

            bool stillActive(void);

            void unloadAllAssets(void);

            CollisionPoint GetCollision(const std::string object, Vec3<float> position);

            /*
                if moving is set to true, the light will rotate around the map
                radius designates the distance to the origin the light will keep on its rotation
            */
            void addDirectionalLight(Vec3<float> position, Vec3<float> target, Color color, bool moving = false, double radius = 0);
            void addPointLight(Vec3<float> position, Color color, bool moving = false, double radius = 0);

            ~Renderer();

        private:
            void _unloadAllObject(void);
            void _unloadAllShader(void);
            void _unloadAllTexture(void);
            void _unloadAllImages(void);
            void _unloadAllTextImages(void);
            TextureCubemap GenTextureCubemap(Shader shader, Texture2D panorama, int size, int format);
            void handleEvents(void);
            void handleCamera(void);

	        float _daytime;
	        float _dayspeed;
	        bool _dayrunning;
            Camera _camera;
            std::shared_ptr<Entity> _skybox;
            Shader _skyboxShader;
	        std::vector<Vector4> _ambientColors;
            Vec4<float> _ambientLight;
            Shader _defaultShader;

            float _camAngle;
            float _camZoom;

            int _defaultAmbientLoc;
            std::vector<LightSource> _lights;
            std::map<std::string, Entity> _objects;
            std::map<std::string, Shader> _shaders;
            std::map<std::string, Texture> _textures;
            std::map<std::string, Image> _images;
            std::map<std::string, Texture> _textImages;
    };

}
