#ifndef SIENGINE_SHADERS_H
#define SIENGINE_SHADERS_H

#include "Engine/GraphicsAPI/OpenGL/Shader.h"
#include "Engine/Configs/ShadersPaths.h"

namespace Shaders
{
    Shader ObjectShader{ShadersPaths::ObjectVertexShader, ShadersPaths::ObjectFragmentShader};
};

#endif //SIENGINE_SHADERS_H
