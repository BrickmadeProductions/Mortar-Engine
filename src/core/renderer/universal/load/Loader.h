#pragma once

#include "Utils.h"
#include "core/renderer/universal/Buffer.h"
#include "core/renderer/universal/Material.h"
#include "core/renderer/universal/Mesh.h"
#include "core/renderer/universal/Model.h"
#include "core/renderer/universal/Shader.h"

namespace MortarCore
{
    struct FaceComparator {
        bool operator()(const std::tuple<uint32_t, uint32_t, uint32_t>& a, const std::tuple<uint32_t, uint32_t, uint32_t>& b) const {
            // Compare first elements
            if (std::get<0>(a) != std::get<0>(b)) return std::get<0>(a) < std::get<0>(b);
            // Compare second elements
            if (std::get<1>(a) != std::get<1>(b)) return std::get<1>(a) < std::get<1>(b);
            // Compare third elements
            return std::get<2>(a) < std::get<2>(b); // Only check the third element if the others are equal
        }
    };
    
    class OBJLoader
    {
    public:
    
        static Ref<Model> LoadObj(const std::string& filepath) 
        {
            
            //vertexMapping
            std::map<std::tuple<uint32_t, uint32_t, uint32_t>, uint32_t, FaceComparator> vertexIndices; //vertexMapping((packed format: POS,NORMAL,UV | indice))

            //raw data (to be flattened using indice buffer)
            std::vector<glm::vec3> positions;
            std::vector<glm::vec3> normals;
            std::vector<glm::vec2> texCoords;

            //vertex data(packed format: POSX,POSY,POSZ,NORMX,NORMY,NORMZ,UVX,UVY)
            std::vector<float> vertexRawBuffer;
            //vertex indicies (packed as pointers to vertexRawBuffer stride)
            std::vector<uint32_t> indicesRawBuffer;

            //file loading
            std::ifstream file(filepath);
            std::string line;

            MRT_CORE_ASSERT(file.is_open());

            while (std::getline(file, line))
            {
                std::stringstream ss(line);
                std::string token;
                ss >> token;

                if (token == "v") { // Vertex position

                    glm::vec3 vertex;
                    ss >> vertex.x >> vertex.y >> vertex.z;

                    positions.push_back(vertex);
                }
                else if (token == "vn") { // Vertex normal
                
                    glm::vec3 normal;
                    ss >> normal.x >> normal.y >> normal.z;

                    normals.push_back(normal);
                }
                else if (token == "vt") { // Vertex texCoord

                    glm::vec2 tex_coord;
                    ss >> tex_coord.x >> tex_coord.y;

                    texCoords.push_back(tex_coord);
                }
                //at this point we have all texCoords and normals, we can check if they are empty
                else if (token == "f") 
                { 
                    std::string faceToken;

                    //3 verts per face
                    while (ss >> faceToken) // split vertexStream by spaces
                    {
                        std::stringstream faceStream(faceToken);
                        
                        //Vertex Indicies
                        uint32_t v = 0, n = 0, t = 0;
                        char slash1, slash2;
                        
                        faceStream >> v;
                        if (faceStream >> slash1 && slash1 == '/') { faceStream >> t; }
                        if (faceStream >> slash2 && slash2 == '/') { faceStream >> n; }

                        //check if we have extra data and validate it to make sure the inputs are correct
                        if (v > positions.size() || (n > 0 && n > normals.size()) || (t > 0 && t > texCoords.size())) 
                        {
                            MRT_PRINT_ERR("Invalid face data in OBJ file!");
                            MRT_CORE_ASSERT(v < positions.size());
                            MRT_CORE_ASSERT(n < normals.size());
                            MRT_CORE_ASSERT(t < texCoords.size());
                        }

                        //find in vertex map, 
                        std::tuple<uint32_t, uint32_t, uint32_t> vertexMap = std::make_tuple(v, n, t);
                        auto vertexMapFound = vertexIndices.find(vertexMap);

                        //check if the vertex is not in the map yet
                        if (vertexMapFound == vertexIndices.end())
                        {
                            uint32_t newIndex = uint32_t(vertexIndices.size());
                            //insert the vertex or replace, it is now in the map so we can check against it later
                            vertexIndices[vertexMap] = newIndex;

                            //push the indice to the indexBuffer
                            indicesRawBuffer.push_back(newIndex);

                            /////////////////\\\\\\\\\\\\\\\\\\\\

                            // OBJ format uses 1-based index, OpenGL uses 0-based, so we subtract 1 from the indices.

                            //this is one stride in the VertexArray
                            //{
                            //push position data
                            glm::vec3 pos = positions[v - 1]; 
                            vertexRawBuffer.push_back(pos.x);
                            vertexRawBuffer.push_back(pos.y);
                            vertexRawBuffer.push_back(pos.z);

                            //push normals and tex coords if we have them, if we don't then push 0s
                            if (n > 0)
                            {
                                glm::vec3 normal = normals[n - 1]; 
                                
                                vertexRawBuffer.push_back(normal.x);
                                vertexRawBuffer.push_back(normal.y);
                                vertexRawBuffer.push_back(normal.z);
                            }
                            else 
                            {
                                vertexRawBuffer.push_back(0.0);
                                vertexRawBuffer.push_back(0.0);
                                vertexRawBuffer.push_back(0.0);
                            }
                            if (t > 0)
                            {
                                glm::vec2 texCoord = texCoords[t - 1]; 
                                vertexRawBuffer.push_back(texCoord.x);
                                vertexRawBuffer.push_back(texCoord.y);
                            }
                            else
                            {
                                vertexRawBuffer.push_back(0.0);
                                vertexRawBuffer.push_back(0.0);
                            }
                            //}
                        
                            
                        }
                        //push the indice to the indexBuffer of the vertex that already existed
                        else indicesRawBuffer.push_back(vertexMapFound->second);
                    }

                   
                }
            }
            
            file.close();
            
            MRT_PRINT("Obj File Parsed.. ");

            MRT_PRINT("Total Indicies " + indicesRawBuffer.size());    

            BufferLayout objLayout =
            {
                { "a_Position", ShaderElement::ShaderElementType::Vec3f },
                
                { "a_Normal", ShaderElement::ShaderElementType::Vec3f },
                
                { "a_TexCoords", ShaderElement::ShaderElementType::Vec2f }
            };

            //create mesh, pass in the vertex data
            Ref<Mesh> mesh = CreateRef<Mesh>(vertexRawBuffer, indicesRawBuffer, objLayout);
            //create mesh (if there is multiple meshes we will load multiple)
            //we now have a valid model
            MRT_PRINT("Mesh Created!...");

            Ref<Model> model = CreateRef<Model>(mesh);

            return CreateRef<Model>(mesh);
        }

    };
}