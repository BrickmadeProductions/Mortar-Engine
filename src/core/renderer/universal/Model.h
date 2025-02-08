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
        Model(Ref<Mesh>& m) : mesh(m) {};

        Ref<Mesh> GetMesh() { return mesh; };

    private:
        Ref<Mesh> mesh;
    };
}
