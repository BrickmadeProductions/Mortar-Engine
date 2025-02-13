#pragma once

#include "core/math/Math.h"
#include "core/renderer/Renderer.h"
#include "core/resource/Mesh.h"
#include "core/resource/Material.h"
#include "Entity3D.h"



namespace MortarCore {
	
    class RenderEntity3D : public Entity3D
	{
	public:

		RenderEntity3D() : Entity3D("RenderEntity3D") { }
		RenderEntity3D(std::string Name) : Entity3D(Name) { }
		virtual ~RenderEntity3D() {}
        
        virtual void BuildRenderData() {}

	protected:
        //VertexArray used for storing any data needed about this objects rendering instructions
        Ref<VertexArray> m_VertexArray;

    private:
	};

	


	
}
