#include "Mesh.h"

#include "Rndr/Core/Log.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>

#include <glad/glad.h>

namespace Rndr {

	namespace {
		const unsigned int ImportFlags =
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_SortByPType |
			aiProcess_PreTransformVertices |
			aiProcess_GenNormals |
			aiProcess_GenUVCoords |
			aiProcess_OptimizeMeshes |
			aiProcess_Debone |
			aiProcess_ValidateDataStructure;
	}

	struct LogStream : public Assimp::LogStream
	{
		static void Initialize()
		{
			if (Assimp::DefaultLogger::isNullLogger())
			{
				Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
				Assimp::DefaultLogger::get()->attachStream(new LogStream, Assimp::Logger::Err | Assimp::Logger::Warn);
			}
		}

		void write(const char* message) override
		{
			RNDR_CORE_ERROR("Assimp error: {0}", message);
		}
	};

	Mesh::Mesh(const std::string& filename)
		: m_FilePath(filename)
	{
		LogStream::Initialize();

		RNDR_CORE_INFO("Loading mesh: {0}", filename.c_str());

		Assimp::Importer importer;
		
		const aiScene* scene = importer.ReadFile(filename, ImportFlags);
		if (!scene || !scene->HasMeshes())
			RNDR_CORE_ERROR("Failed to load mesh file: {0}", filename);

		aiMesh* mesh = scene->mMeshes[0];

		RNDR_CORE_ASSERT(mesh->HasPositions(), "Meshes require positions.");
		RNDR_CORE_ASSERT(mesh->HasNormals(), "Meshes require normals.");

		m_VertexArray.reset(VertexArray::Create());

		m_Vertices.reserve(mesh->mNumVertices);

		// Extract vertices from model
		for (size_t i = 0; i < m_Vertices.capacity(); i++) 
		{
			Vertex vertex;
			vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
			// vertex.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

			// if (mesh->HasTangentsAndBitangents())
			// {
			// 	vertex.Tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
			// 	vertex.Binormal = { mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z };
			// }

			if (mesh->HasTextureCoords(0))
				vertex.Texcoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
			m_Vertices.push_back(vertex);
		}

		// m_VertexBuffer.reset(VertexBuffer::Create());
		m_VertexBuffer = VertexBuffer::Create((float*)m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			// { ShaderDataType::Float3, "a_Normal" },
			// { ShaderDataType::Float3, "a_Tangent" },
			// { ShaderDataType::Float3, "a_Binormal" },
			{ ShaderDataType::Float2, "a_Texcoord" }
		};
		m_VertexBuffer->SetLayout(layout);
		// m_VertexBuffer->SetData(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		// Extract indices from model
		m_Indices.reserve(mesh->mNumFaces);
		for (size_t i = 0; i < m_Indices.capacity(); i++)
		{
			RNDR_CORE_ASSERT(mesh->mFaces[i].mNumIndices == 3, "Must have 3 indices.");
			m_Indices.push_back({ mesh->mFaces[i].mIndices[0], mesh->mFaces[i].mIndices[1], mesh->mFaces[i].mIndices[2] });
		}

		// m_IndexBuffer.reset(IndexBuffer::Create());
		m_IndexBuffer = IndexBuffer::Create((uint32_t*)m_Indices.data(), m_Indices.size() * sizeof(Index));
		// m_IndexBuffer->SetData(m_Indices.data(), m_Indices.size() * sizeof(Index));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		RNDR_CORE_INFO("Loaded mesh: {0}", filename);
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::Render()
	{
		// // TODO: Sort this out
		// m_VertexBuffer->Bind();
		// m_IndexBuffer->Bind();
		// RNDR_RENDER_S({
		// 	glEnableVertexAttribArray(0);
		// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

		// 	glEnableVertexAttribArray(1);
		// 	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Normal));

		// 	glEnableVertexAttribArray(2);
		// 	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Tangent));

		// 	glEnableVertexAttribArray(3);
		// 	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Binormal));

		// 	glEnableVertexAttribArray(4);
		// 	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Texcoord));
		// });
		// Renderer::DrawIndexed(m_IndexBuffer->GetCount());
	}

}