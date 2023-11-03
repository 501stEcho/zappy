/*
** EPITECH PROJECT, 2023
** Renderer
** File description:
** zappy
*/

#include "Renderer/Renderer.hpp"
#include <memory>
#include <raylib.h>

zappy::LightSource::LightSource(Light light, bool moving, double radius, Axis axis)
{
    _light = light;
    _moving = moving;
    _radius = radius;
    _axis = axis;
}

void zappy::LightSource::adaptPosition(double sunAngle)
{
    if (_moving) {
        switch (_axis) {
        case (X):
            _light.position.x = 0;
            _light.position.y = sinf(sunAngle) * _radius;
            _light.position.z = cosf(sunAngle) * _radius;
            break;

        case (Y):
            _light.position.x = cosf(sunAngle) * _radius;
            _light.position.y = 0;
            _light.position.z = sinf(sunAngle) * _radius;
            break;

        case (Z):
            _light.position.x = cosf(sunAngle) * _radius;
            _light.position.y = sinf(sunAngle) * _radius;
            _light.position.z = 0;
            break;
        }
    }
}

Light &zappy::LightSource::getLight()
{
    return (_light);
}

zappy::Renderer::Renderer()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTraceLogLevel(LOG_FATAL);
    InitWindow(WIN3D_WIDTH, WIN3D_HEIGHT, "ZAPPY");
    rlDisableBackfaceCulling();

    _daytime = 0.2f;
    _dayspeed = 0.015f;
    _dayrunning = true;

    _camera.position = Vector3{20.0, 20.0, 20.0};
    _camera.target = Vector3{0.0f, 8.0f, 0.0f};
    _camera.up = Vector3{0.0f, 1.6f, 0.0f};
    _camera.fovy = 45.0f;
    _camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    _defaultShader = LoadShader(TextFormat("Sources/shaders/default.vs", GLSL_VERSION),
    TextFormat("Sources/shaders/default.fs", GLSL_VERSION));
    _defaultShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(_defaultShader, "viewpos");
    _defaultAmbientLoc = GetShaderLocation(_defaultShader, "ambient");

    _camAngle = 125.0;
    _camZoom = 1.5;
}

void zappy::Renderer::setAmbientColors(const std::string pathName)
{
    Image ambientColorsImage = LoadImage(pathName.c_str());
    Color *ambientColorsTemp = LoadImageColors(ambientColorsImage);
    int ambientColorsNumber = ambientColorsImage.width;

    _ambientColors.clear();
    for (int i = 0; i < ambientColorsNumber; i++)
        _ambientColors.push_back(ColorNormalize(ambientColorsTemp[i]));
    UnloadImageColors(ambientColorsTemp);
    UnloadImage(ambientColorsImage);
}

void zappy::Renderer::setSkybox(const std::string pathName, const std::string vertexShaderPath, const std::string fragmentShaderPath,
const std::string cubemapVertexShader, const std::string cubemapFragmentShader)
{
    Mesh cube = GenMeshCube(100.0f, 100.0f, 100.0f);
    std::shared_ptr<Entity> skybox = std::make_shared<Entity>(cube);
    Shader shader = LoadShader(TextFormat(vertexShaderPath.c_str(), GLSL_VERSION), TextFormat(fragmentShaderPath.c_str(), GLSL_VERSION));
    Shader shdrCubemap = LoadShader(TextFormat(cubemapVertexShader.c_str(), GLSL_VERSION), TextFormat(cubemapFragmentShader.c_str(), GLSL_VERSION));
    int param0 = MATERIAL_MAP_CUBEMAP;
    int param1 = 1;
    int param2 = 1;
    int param3 = 0;

    skybox->loadShader(shader);
    skybox->addLocation("environmentMap");
    skybox->addLocation("doGamma");
    skybox->addLocation("vflipped");

    skybox->setShaderValue("environmentMap", &param0, SHADER_UNIFORM_INT);
    skybox->setShaderValue("doGamma", &param1, SHADER_UNIFORM_INT);
    skybox->setShaderValue("vflipped", &param2, SHADER_UNIFORM_INT);

    SetShaderValue(shdrCubemap, GetShaderLocation(shdrCubemap, "equirectangularMap"), &param3, SHADER_UNIFORM_INT);

    Texture2D texHDR;

    texHDR = LoadTexture(pathName.c_str());

    skybox->_model.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = GenTextureCubemap(shdrCubemap, texHDR, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    _skyboxShader = shdrCubemap;
    _skybox = skybox;
}

void zappy::Renderer::addShader(const std::string shaderName, const std::string vertexShaderPath, const std::string fragmentShaderPath)
{
    Shader shader = LoadShader(TextFormat(vertexShaderPath.c_str(), GLSL_VERSION),
    TextFormat(fragmentShaderPath.c_str(), GLSL_VERSION));

    _shaders[shaderName] = shader;
}

void zappy::Renderer::addObject(const std::string objName, const std::string objModelPath)
{
    _objects.insert({objName, Entity(objModelPath)});
}

void zappy::Renderer::addTexture(const std::string textureName, const std::string pathName)
{
    Image image = LoadImage(pathName.c_str());
    Texture texture = LoadTextureFromImage(image);

    _images.insert({textureName, image});
    _textures.insert({textureName, texture});
}

void zappy::Renderer::setObjectShader(const std::string objName, const std::string shaderName)
{
    if (_objects.find(objName) == _objects.end())
        throw EntityException(objName + " : unknown object");
    if (_shaders.find(shaderName) == _shaders.end())
        throw EntityException(shaderName + " : unknown shader");
    _objects.at(objName).loadShader(_shaders[shaderName]);
}

void zappy::Renderer::addDirectionalLight(Vec3<float> position, Vec3<float> target, Color color, bool moving, double radius)
{
    if (_shaders.size() == 0)
        throw RendererException("No existing shader");

    Vector3 pos = {position.x, position.y, position.z};
    Vector3 tar = {target.x, target.y, target.z};
    Light nlight = CreateLight(LIGHT_DIRECTIONAL, pos, tar, color, _defaultShader);
    _lights.push_back(LightSource(nlight, moving, radius, Z));
}

void zappy::Renderer::addPointLight(Vec3<float> position, Color color, bool moving, double radius)
{
    if (_shaders.size() == 0)
        throw RendererException("No existing shader");
    Vector3 pos = {position.x, position.y, position.z};
    Vector3 tar = Vector3Zero();
    Light nlight = CreateLight(LIGHT_POINT, pos, tar, color, _defaultShader);
    _lights.push_back(LightSource(nlight, moving, radius, Z));
}

void zappy::Renderer::actualize(void)
{
    handleEvents();
    handleCamera();

    if (_dayrunning) {
        _daytime += _dayspeed * GetFrameTime();
        while (_daytime > 1.0f) {
            _daytime -= 1.0;
        }
    }

    float sunAngle = Lerp(-90, 270, _daytime) * DEG2RAD;
    float nDaytime = sinf(sunAngle);
    int iDaytime = ((nDaytime + 1.0f) / 2.0f) * (float)(_ambientColors.size() - 1);

    _ambientLight.x = _ambientColors[iDaytime].x;
    _ambientLight.y = _ambientColors[iDaytime].y;
    _ambientLight.z = _ambientColors[iDaytime].z;
    _ambientLight.w = Lerp(0.05f, 0.25f, ((nDaytime + 1.0f) / 2.0f));

    Vec3<float> camPos(_camera.position.x, _camera.position.y, _camera.position.z);
    float cameraPos[3] = {_camera.position.x, _camera.position.y, _camera.position.z};
    SetShaderValue(_defaultShader, _defaultShader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

    for (unsigned int i = 0; i < _lights.size(); i++) {
        _lights[i].adaptPosition(sunAngle);
        UpdateLightValues(_defaultShader, _lights[i].getLight());
    }
    for (auto &it : _objects) {
        it.second.updateCameraPosition(camPos);
        it.second.updateAmbientLight(_ambientLight);
        for (unsigned int i = 0; i < _lights.size(); i++)
            it.second.updateLight(_lights[i].getLight());
    }
}

void zappy::Renderer::handleCamera(void)
{
    Vector3 position = {0, 0, 0};
    Vector3 rotation = {0, 0, 0};
    float wheel = GetMouseWheelMove();
    float zoom = 0.0;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 diff = GetMouseDelta();
        position.x += diff.y / 10;
        position.y -= diff.x / 10;
    }

    if (IsKeyDown(KEY_RIGHT)) {
        rotation.x += 1;
    }

    if (IsKeyDown(KEY_LEFT)) {
        rotation.x -= 1;
    }

    if (IsKeyDown(KEY_DOWN)) {
        if (_camAngle < 180.0) {
            rotation.y += 1;
            _camAngle += 1;
        }
    }

    if (IsKeyDown(KEY_UP)) {
        if (_camAngle > 125.0) {
            rotation.y -= 1;
            _camAngle -= 1;
        }
    }

    if (_camZoom != 0 && !(_camZoom + wheel * 0.1 < 0.0 || _camZoom + wheel * 0.1 > 10)) {
        _camZoom += 0.1 * wheel;
        zoom -= wheel;
    }

    UpdateCameraPro(&_camera, position, rotation, zoom);
}

void zappy::Renderer::handleEvents(void)
{
    if (IsKeyDown(KEY_SPACE)) {
        _daytime += _dayspeed * (5.0f - (float)_dayrunning) * GetFrameTime();
        while (_daytime > 1.0f) {
            _daytime -= 1.0;
        }
    }
}

void zappy::Renderer::displayObject(const std::string objectName, Vec3<float> position, Vec3<float> orientation)
{
    Vector3 pos = {position.x, position.y, position.z};
    Vector3 ori = {0, DEG2RAD * orientation.y, 0};
    Vector3 nul = {0, 0, 0};

    if (_objects.find(objectName) != _objects.end()) {
        _objects.at(objectName)._model.transform = MatrixRotateXYZ(ori);
        DrawModel(_objects.at(objectName)._model, pos, 1.0, WHITE);
        _objects.at(objectName)._model.transform = MatrixRotateXYZ(nul);
    } else
        throw RendererException(objectName + " : unknown object");
}

void zappy::Renderer::displayTexture(const std::string textureName, float scale, Vec2<float> position)
{
    Vector2 pos = {position.x, position.y};

    if (_textures.find(textureName) != _textures.end()) {
        DrawTextureEx(_textures.at(textureName), pos, 0, scale, WHITE);
    } else
        throw RendererException(textureName + " : unknown texture");
}

void zappy::Renderer::displayBillboardTexture(const std::string textureName, float size, Vec3<float> position, bool center)
{
    (void)center;
    Vector3 pos = {position.x, position.y, position.z};

    if (_textures.find(textureName) != _textures.end()) {
        DrawBillboard(_camera, _textures.at(textureName), pos, size, WHITE);
    } else
        throw RendererException(textureName + " : unknown texture");
}

void zappy::Renderer::displayBoundingBox(const std::string objectName, Vec3<float> position)
{
    if (_objects.find(objectName) != _objects.end()) {
        BoundingBox box = GetModelBoundingBox(_objects.at(objectName)._model);

        box.min.x += position.x;
        box.min.y += position.y;
        box.min.z += position.z;

        box.max.x += position.x;
        box.max.y += position.y;
        box.max.z += position.z;

        DrawBoundingBox(box, RAYWHITE);
    } else
        throw RendererException(objectName + " : unknown object");
}

void zappy::Renderer::drawText(const std::string text, Vec2<float> position, int FontSize, Color color)
{
    DrawText(text.c_str(), position.x, position.y, FontSize, color);
}

void zappy::Renderer::drawTextInImage(const std::string textureName, const std::string msg, Vec3<float> position, float fontSize, Color color)
{
    Image image;
    if (_textImages.find(textureName + msg) == _textImages.end()) {
        if (_images.find(textureName) != _images.end()) {
            image = _images.at(textureName);
        } else if (_textures.find(textureName) != _textures.end()) {
            image = LoadImageFromTexture(_textures.at(textureName));
            _images.insert({textureName, image});
        } else
            throw RendererException(textureName + " : unknown texture");
        Image imageCopy = ImageCopy(image);
        ImageDrawText(&imageCopy, msg.c_str(), 100, 100, fontSize, color);
        Texture tex = LoadTextureFromImage(imageCopy);
        _textImages.insert({textureName + msg, tex});
        UnloadImage(imageCopy);
    }
    Texture tex = _textImages.at(textureName + msg);
    Vector3 pos = {position.x, position.y, position.z};
    DrawBillboard(_camera, tex, pos, 1.0, WHITE);
}

void zappy::Renderer::drawCube(Vec3<float> position, Vec3<float> size, Color color)
{
    Vector3 pos = {position.x, position.y, position.z};
    Vector3 siz = {size.x, size.y, size.z};

    DrawCube(pos, siz.x, siz.y, siz.z, color);
}

bool zappy::Renderer::stillActive(void)
{
    return (!WindowShouldClose());
}

void zappy::Renderer::enableDrawing(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void zappy::Renderer::disableDrawing(void)
{
    EndDrawing();
}

void zappy::Renderer::enable3DMode(void)
{
    BeginMode3D(_camera);
}

void zappy::Renderer::disable3DMode(void)
{
    EndMode3D();
}

void zappy::Renderer::enableBlendMode(void)
{
    BeginBlendMode(BLEND_ALPHA);
    // BeginBlendMode(BLEND_ADDITIVE);
    // BeginBlendMode(BLEND_MULTIPLIED);
    // BeginBlendMode(BLEND_ADD_COLORS);
    // BeginBlendMode(BLEND_SUBTRACT_COLORS);
    // BeginBlendMode(BLEND_ALPHA_PREMULTIPLY);
    // BeginBlendMode(BLEND_CUSTOM);
    // BeginBlendMode(BLEND_CUSTOM_SEPARATE);
}

void zappy::Renderer::disableBlendMode(void)
{
    EndBlendMode();
}

bool zappy::Renderer::keyDown(KeyBind key)
{
    switch (key) {
    case (MOUSE_LEFT):
        return (IsMouseButtonDown(MOUSE_BUTTON_LEFT));
        break;

    case (MOUSE_RIGHT):
        return (IsMouseButtonDown(MOUSE_BUTTON_RIGHT));
        break;

    case (RIGHT):
        return (IsKeyDown(KEY_RIGHT));
        break;

    case (LEFT):
        return (IsKeyDown(KEY_LEFT));
        break;

    case (UP):
        return (IsKeyDown(KEY_UP));
        break;

    case (DOWN):
        return (IsKeyDown(KEY_DOWN));
        break;

    default:
        return (false);
        break;
    }
}

bool zappy::Renderer::keyUp(KeyBind key)
{
    switch (key) {
    case (MOUSE_LEFT):
        return (IsMouseButtonUp(MOUSE_BUTTON_LEFT));
        break;

    case (MOUSE_RIGHT):
        return (IsMouseButtonUp(MOUSE_BUTTON_RIGHT));
        break;

    case (RIGHT):
        return (IsKeyUp(KEY_RIGHT));
        break;

    case (LEFT):
        return (IsKeyUp(KEY_LEFT));
        break;

    case (UP):
        return (IsKeyUp(KEY_UP));
        break;

    case (DOWN):
        return (IsKeyUp(KEY_DOWN));
        break;

    default:
        return (false);
        break;
    }
}

bool zappy::Renderer::keyPressed(KeyBind key)
{
    switch (key) {
    case (MOUSE_LEFT):
        return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
        break;

    case (MOUSE_RIGHT):
        return (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT));
        break;

    case (RIGHT):
        return (IsKeyPressed(KEY_RIGHT));
        break;

    case (LEFT):
        return (IsKeyPressed(KEY_LEFT));
        break;

    case (UP):
        return (IsKeyPressed(KEY_UP));
        break;

    case (DOWN):
        return (IsKeyPressed(KEY_DOWN));
        break;

    default:
        return (false);
        break;
    }
}

bool zappy::Renderer::keyReleased(KeyBind key)
{
    switch (key) {
    case (MOUSE_LEFT):
        return (IsMouseButtonReleased(MOUSE_BUTTON_LEFT));
        break;

    case (MOUSE_RIGHT):
        return (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT));
        break;

    case (RIGHT):
        return (IsKeyReleased(KEY_RIGHT));
        break;

    case (LEFT):
        return (IsKeyReleased(KEY_LEFT));
        break;

    case (UP):
        return (IsKeyReleased(KEY_UP));
        break;

    case (DOWN):
        return (IsKeyReleased(KEY_DOWN));
        break;

    default:
        return (false);
        break;
    }
}

int zappy::Renderer::getWindowWidth(void)
{
    return (GetScreenWidth());
}

int zappy::Renderer::getWindowHeight(void)
{
    return (GetScreenHeight());
}

void zappy::Renderer::displayLights(void)
{
    for (unsigned int i = 0; i < _lights.size(); i++) {
        DrawSphereEx(_lights[i].getLight().position, 10, 8, 8, _lights[i].getLight().color);
    }
}

void zappy::Renderer::displaySkybox(void)
{
    if (!_skybox)
        throw RendererException("No skybox loaded");

    rlDisableBackfaceCulling();
    rlDisableDepthMask();
    DrawModel(_skybox->_model, {0, 0, 0}, 1.0f, WHITE);
    rlEnableBackfaceCulling();
    rlEnableDepthMask();
}

zappy::CollisionPoint zappy::Renderer::GetCollision(const std::string objectName, Vec3<float> position)
{
    if (_objects.find(objectName) == _objects.end())
        throw RendererException("Unknown object");

    Ray ray = GetMouseRay(GetMousePosition(), _camera);
    Entity &target = _objects.at(objectName);
    RayCollision collision;
    Matrix transform = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    collision.distance = FLT_MAX;
    collision.hit = false;

    transform.m0 = 1;
    transform.m5 = 1;
    transform.m10 = 1;
    transform.m15 = 1;
    transform.m12 = position.x;
    transform.m13 = position.y;
    transform.m14 = position.z;

    int meshCount = target._model.meshCount;

    RayCollision meshHit;
    for (int i = 0; i < meshCount; i++) {
        meshHit = GetRayCollisionMesh(ray, target._model.meshes[i], transform);
        if (meshHit.hit) {
            if ((!collision.hit) || (collision.distance > meshHit.distance)) {
                collision = meshHit;
            }
        }
    }
    if (collision.hit) {
        Vec3<float> point(collision.point.x, collision.point.y, collision.point.z);
        Vec3<float> normal(collision.normal.x, collision.normal.y, collision.normal.z);
        return (CollisionPoint(collision.hit, collision.distance, point, normal));
    }
    return (CollisionPoint());
}

TextureCubemap zappy::Renderer::GenTextureCubemap(Shader shader, Texture2D panorama, int size, int format)
{
    TextureCubemap cubemap;

    rlDisableBackfaceCulling();
    unsigned int rbo = rlLoadTextureDepth(size, size, true);
    cubemap.id = rlLoadTextureCubemap(0, size, format);

    unsigned int fbo = rlLoadFramebuffer(size, size);
    rlFramebufferAttach(fbo, rbo, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER, 0);
    rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X, 0);

    rlFramebufferComplete(fbo);

    rlEnableShader(shader.id);

    Matrix matFboProjection = MatrixPerspective(90.0 * DEG2RAD, 1.0, RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR);
    rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_PROJECTION], matFboProjection);

    Matrix fboViews[6] = {
    MatrixLookAt((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){1.0f, 0.0f, 0.0f}, (Vector3){0.0f, -1.0f, 0.0f}),
    MatrixLookAt((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){-1.0f, 0.0f, 0.0f}, (Vector3){0.0f, -1.0f, 0.0f}),
    MatrixLookAt((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 1.0f, 0.0f}, (Vector3){0.0f, 0.0f, 1.0f}),
    MatrixLookAt((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, -1.0f, 0.0f}, (Vector3){0.0f, 0.0f, -1.0f}),
    MatrixLookAt((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, 1.0f}, (Vector3){0.0f, -1.0f, 0.0f}),
    MatrixLookAt((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, -1.0f}, (Vector3){0.0f, -1.0f, 0.0f})};

    rlViewport(0, 0, size, size);

    rlActiveTextureSlot(0);
    rlEnableTexture(panorama.id);

    for (int i = 0; i < 6; i++) {
        rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_VIEW], fboViews[i]);

        rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X + i, 0);
        rlEnableFramebuffer(fbo);

        rlClearScreenBuffers();
        rlLoadDrawCube();
    }

    rlDisableShader();
    rlDisableTexture();
    rlDisableFramebuffer();
    rlUnloadFramebuffer(fbo);

    rlViewport(0, 0, rlGetFramebufferWidth(), rlGetFramebufferHeight());
    rlEnableBackfaceCulling();

    cubemap.width = size;
    cubemap.height = size;
    cubemap.mipmaps = 1;
    cubemap.format = format;

    return cubemap;
}

zappy::Renderer::~Renderer()
{
    CloseWindow();
}

void zappy::Renderer::unloadAllAssets(void)
{
    _unloadAllShader();
    _unloadAllTexture();
    _unloadAllTextImages();
    _unloadAllImages();
    _unloadAllObject();
    UnloadShader(_skyboxShader);
    UnloadShader(_skybox->_model.materials[0].shader);
    _skybox->unloadModel();
}

void zappy::Renderer::_unloadAllObject(void)
{
    for (auto &it : _objects) {
        it.second.unloadModel();
    }
}

void zappy::Renderer::_unloadAllShader(void)
{
    for (auto &it : _shaders) {
        UnloadShader(it.second);
    }
}

void zappy::Renderer::_unloadAllTexture(void)
{
    for (auto &it : _textures) {
        UnloadTexture(it.second);
    }
}

void zappy::Renderer::_unloadAllImages(void)
{
    for (auto &it : _images) {
        UnloadImage(it.second);
    }
}

void zappy::Renderer::_unloadAllTextImages(void)
{
    for (auto &it : _textImages) {
        UnloadTexture(it.second);
    }
}
