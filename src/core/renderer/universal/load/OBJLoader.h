#pragma once

#include "Utils.h"
#include "core/renderer/universal/Buffer.h"
#include "core/renderer/universal/Material.h"
#include "core/renderer/universal/Mesh.h"
#include "core/renderer/universal/Model.h"
#include "core/renderer/universal/Shader.h"

namespace MortarCore
{
    class OBJLoader
    {
        static Ref<VertexBuffer> VertsToBufferObject(const std::vector<Vertex>& vecList) {
            // The size of the float array will be 3 * the number of glm::vec3 elements
            uint32_t size = vecList.size() * 3;  // Each Vertex has 6 float values: vertex (x, y, z)
            float* floatArray = new float[size];

            // Copy Vertex values into the float array
            for (size_t i = 0; i < vecList.size(); ++i)
            {
                floatArray[i * 3 + 0] = vecList[i].position.x;
                floatArray[i * 3 + 1] = vecList[i].position.y;
                floatArray[i * 3 + 2] = vecList[i].position.z;
            }

            return VertexBuffer::CreateBuffer(floatArray, size);
        }

        static Ref<IndexBuffer> IndiciesToBufferObject(const std::vector<uint32_t>& indexList) {
            // The size of the float array will be the size since each vertex is an index
            uint32_t size = indexList.size(); 
            uint32_t* uintArray = new uint32_t[size];

            // convert to uint32_t pointer
            for (size_t i = 0; i < indexList.size(); ++i) uintArray[i] = indexList[i];

            return IndexBuffer::CreateBuffer(uintArray, size);
        }   

        static Model& LoadObj(const std::string& filepath) 
        {
            std::ifstream file(filepath);

            MRT_CORE_ASSERT(file.is_open())

            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> normals;
            std::vector<uint32_t> indices;
            
            std::string line;

            while (std::getline(file, line))
            {
                std::stringstream ss(line);
                std::string token;
                ss >> token;

                if (token == "v") { // Vertex position
                    glm::vec3 vertex;
                    ss >> vertex.x >> vertex.y >> vertex.z;
                    vertices.push_back(vertex);
                }
                else if (token == "vn") { // Vertex normal
                    glm::vec3 normal;
                    ss >> normal.x >> normal.y >> normal.z;
                    normals.push_back(normal);
                }
                else if (token == "f") { // Face
                    GLuint vertexIndex[3], normalIndex[3];
                    char slash; // To consume '/'
                    for (int i = 0; i < 3; i++) {
                        ss >> vertexIndex[i] >> slash >> slash >> normalIndex[i];
                        indices.push_back(vertexIndex[i] - 1); // OBJ indices are 1-based, so subtract 1
                    }
                }
            }
            file.close();

            std::vector<Vertex> finalVertArray;

            //pack all vertices
            for (uint32_t i : indices) finalVertArray.push_back({ vertices[i], normals[i] });

            //create shader program
            Ref<Shader> defaultSpatial = Shader::CreateProgram("defaultSpatial.vert", "defaultSpatialF.frag");
            //create material
            Ref<Material> mat = CreateRef<Material>(defaultSpatial);
            //create mesh
            Ref<Mesh> mesh = CreateRef<Mesh>(mat, finalVertArray);
            //create model (if there is multiple meshes we will load multiple)
            //load model
            Model model(mesh);
            //we now have a valid model
            return model;
        }
           
    };
}