#pragma once

#include "Utils.h"
#include "Resource.h"

namespace MortarCore
{
struct Mesh;

    struct Model : public Resource
    {
    public:

        Model() = default;
        Model(Model&) = default;
        Model(std::vector<Ref<Mesh>>& ms) : m_Meshes(ms) {}
        Model(Ref<Mesh>& m) { m_Meshes.push_back(m); }
        
        Ref<Mesh>& GetMesh(int index) { return m_Meshes[index]; };
        std::vector<Ref<Mesh>>& GetMeshArray() { return m_Meshes; };

    private:
    
        std::vector<Ref<Mesh>> m_Meshes;
    };
}
