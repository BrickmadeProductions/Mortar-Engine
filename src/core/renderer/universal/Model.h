#pragma once

#include "Utils.h"
#include "Mesh.h"

namespace MortarCore
{

    //MODEL STRUCTURE
    struct Model
    {
    public:

        Model() = default;
        Model(const Model&) = default;
        Model(Ref<Mesh>& m) : m_Mesh(m) {};

        Ref<Mesh>& GetMesh() { return m_Mesh; };

    private:
        Ref<Mesh> m_Mesh;
    };
}
