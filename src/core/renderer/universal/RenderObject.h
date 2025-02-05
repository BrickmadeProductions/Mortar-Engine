#pragma once

#include "Shader.h"

namespace MortarCore {

	//MATERIAL STRUCTURE
	struct Material
	{
	public:

		Material(Shader& shader) :
			m_Shader(shader)
		{

		}

	private:

		Shader& m_Shader;
	};

	//MESH STRUCTURE
	struct Mesh
	{
	public:

		Mesh(Material& material, VertexBuffer& vertBuffer, IndexBuffer& indexBuffer)
			: m_Material(material),
			m_VertexBuffer(m_VertexBuffer),
			m_IndexBuffer(m_IndexBuffer)
		{
			
		}

	private:

		Material& m_Material;
		VertexBuffer& m_VertexBuffer;
		IndexBuffer& m_IndexBuffer;
	};

	//MODEL STRUCTURE
	struct Model
	{
	public:

		Model() = default;
		Model(const Model&) = default;
		Model(eastl::vector<Ref<Mesh>>& m) : meshes(m) {};

		Ref<Mesh> GetMesh(uint32_t meshIndex) { return meshes[meshIndex]; };
		void AddMesh(Ref<Mesh>& mesh) { meshes.push_back(mesh); };

	private:
		eastl::vector<Ref<Mesh>> meshes;
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