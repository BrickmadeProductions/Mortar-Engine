#pragma once

#include "Utils.h"
#include "core/renderer/universal/Shader.h"

namespace MortarCore
{
    class ShaderLibrary
    {

        Ref<Shader> GetShader(uint32_t shaderID) { return m_CachedShaders[shaderID]; }
        void CacheShader(Ref<Shader>& shader) { m_CachedShaders.emplace(shader->GetShaderID(), shader); }

        private:
        
            std::unordered_map<uint32_t, Ref<Shader>> m_CachedShaders;
    };

}