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
        Model(Ref<Mesh>& m) { meshes.emplace(&m); };
        Model(eastl::vector<Ref<Mesh>>& m) : meshes(m) {};

        Ref<Mesh> GetMesh(uint32_t meshIndex) { return meshes[meshIndex]; };
        void AddMesh(Ref<Mesh>& mesh) { meshes.push_back(mesh); };

    private:
        eastl::vector<Ref<Mesh>> meshes;
    };
}
