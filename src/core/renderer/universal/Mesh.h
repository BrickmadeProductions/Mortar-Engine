#pragma once

#include "Material.h"
#include "Utils.h"

namespace MortarCore {
    
	struct Vertex 
	{
        glm::vec3 position;
        glm::vec3 normal;
    };

	//MESH STRUCTURE
	struct Mesh
	{
		Mesh() = default;
		Mesh(Mesh&) = default;
		Mesh(Ref<Material>& mat, const std::vector<Vertex>& vertArray) : m_Material(mat), m_VertexArray(vertArray) {}

		Ref<Material> m_Material;
		const std::vector<Vertex> m_VertexArray;
	};


}

//vao.Bind();

//OPEN_GL_DEBUG(printf("Bind Model: %i\n", glGetError()));
//OPEN_GL_DEBUG(printf("VAO ID: %i\n", vao.ID));

//material->shader->bindAttribLocation(0, "position");

//material->shader->bindAttribLocation(1, "textureCoords");

//material->shader->bindAttribLocation(2, "normal");

////then link data about the attributes (normals, uvs, etc.)


//vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(GLfloat) * 3, (void*)0); //CORDINATES
//OPEN_GL_DEBUG(printf("Link Attrib To VAO (Vertices): %i\n", glGetError()));

//vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, sizeof(GLfloat) * 2, (void*)(3 * sizeof(float))); //TEX COORDS
//OPEN_GL_DEBUG(printf("Link Attrib To VAO (UVs): %i\n", glGetError()));

//vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(GLfloat) * 3, (void*)(6 * sizeof(float)));	//NORMALS
//OPEN_GL_DEBUG(printf("Link Attrib To VAO (Normals): %i\n", glGetError()));

//vao.Unbind();
//vbo.Unbind();
//ebo.Unbind();