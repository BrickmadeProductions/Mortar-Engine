#pragma once

#include "core/renderer/universal/VertexArray.h"
#include "core/renderer/Renderer.h"
#include "core/renderer/universal/load/ImageLoader.h"

namespace MortarCore
{
    class RenderAPI
    {
    public:

        enum class API
        {
            OPENGL,
            VULKAN
        };

    public:

        virtual ~RenderAPI() = default;

        virtual int Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawInstanced(const Ref<VertexArray>& VertexArray, uint32_t vertCount, uint32_t instanceCount) = 0;

        virtual void LoadTexture(Ref<Texture>& texture) = 0;

        std::vector<Ref<Material>>& GetCachedMaterials() { return m_CachedMaterials; }
        std::vector<Ref<Texture>>& GetCachedTextures() { return m_CachedTextures; }

        static API GetAPI() { return s_API; }
        static void SetAPI(API api) { s_API = api; }

        static Scope<RenderAPI> Create();

    protected:

        static API s_API;
        std::vector<Ref<Material>> m_CachedMaterials;
        std::vector<Ref<Texture>> m_CachedTextures;

    };

} 
