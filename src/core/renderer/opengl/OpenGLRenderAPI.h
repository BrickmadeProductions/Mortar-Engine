#pragma once

#include "core/renderer/RenderAPI.h"

namespace MortarCore
{
    class OpenGLRenderAPI : public RenderAPI
    {
    public:

        OpenGLRenderAPI();
        virtual ~OpenGLRenderAPI();
        
        int Init() override;
        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void SetClearColor(const glm::vec4& color) override;
        void Clear() override;

        void DrawInstanced(const Ref<VertexArray>& VertexArray, uint32_t vertCount, uint32_t instanceCount) override;
        void LoadTexture(Ref<Texture>& texture) override;

    };
}