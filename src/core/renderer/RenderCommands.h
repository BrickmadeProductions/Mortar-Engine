#pragma once

#include "core/renderer/RenderAPI.h"
#include "Utils.h"

//this class creates calls to the virtual renderAPI scope that is defined through window creation
namespace MortarCore
{
    class RenderCommands
    {
        public:

            static int InitializeAPI()
            {
                return s_RenderAPI->Init();
            }
            static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
            {
                s_RenderAPI->SetViewport(x, y, width, height);
            }
            static void SetClearColor(const glm::vec4& color)
            {
                s_RenderAPI->SetClearColor(color);
            }
            static void Clear()
            {
                s_RenderAPI->Clear();
            }
            static void DrawInstanced(const Ref<VertexArray>& VertexArray, uint32_t vertCount, uint32_t instanceCount)
            {
                s_RenderAPI->DrawInstanced(VertexArray, vertCount, instanceCount);
            }

            //cache
            static void CacheMaterial(Ref<Material> mat)
            { 
                s_RenderAPI->GetCachedMaterials().push_back(mat); 
            }
            static Ref<Material> GetCachedMaterial(uint32_t index)
            { 
                return s_RenderAPI->GetCachedMaterials()[index];
            }
            static void CacheTexture(Ref<Texture> tex)
            {
                s_RenderAPI->LoadTexture(tex);
            }
            static Ref<Texture> GetCachedTexture(uint32_t index)
            {
                return s_RenderAPI->GetCachedTextures()[index];
            }
            static Scope<RenderAPI>& GetRenderAPI() {
                return s_RenderAPI;
            }

        private:

            static Scope<RenderAPI> s_RenderAPI;
    };
    
}