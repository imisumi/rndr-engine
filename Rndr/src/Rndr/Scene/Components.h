#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>


#include "Rndr/Renderer/Material.h"
//  

#include "SceneCamera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Rndr/Renderer/Mesh.h"

#include "Rndr/Core/Base.h"

#include "Rndr/Core/UUID.h"

namespace Rndr
{
	struct IDComponent
	{
		UUID ID;

		IDComponent() = default;
		IDComponent(const IDComponent&) = default;
	};

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct ChildComponent
	{
		std::vector<UUID> Children;

		ChildComponent() = default;
		ChildComponent(const ChildComponent&) = default;

		void AddChild(UUID child)
		{
			Children.push_back(child);
		}

		void RemoveChild(UUID child)
		{
			auto it = std::find(Children.begin(), Children.end(), child);
			if (it != Children.end())
				Children.erase(it);
		}

		bool HasChild(UUID child)
		{
			auto it = std::find(Children.begin(), Children.end(), child);
			return it != Children.end();
		}

		bool HasChildren()
		{
			return !Children.empty();
		}
	};

	struct ParentComponent
	{
		UUID Parent = 0;

		ParentComponent() = default;
		ParentComponent(const ParentComponent&) = default;
		ParentComponent(UUID parent)
			: Parent(parent) {}
	};

	struct TransformComponent
	{
		// glm::mat4 Transform{ 1.0f };
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f }; // in Radians
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		// glm::mat4 WorldTransform = glm::mat4(1.0f);
		glm::vec3 WorldTranslation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 WorldRotation = { 0.0f, 0.0f, 0.0f }; // in Radians
		glm::vec3 WorldScale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 translation = glm::translate(glm::mat4(1.0f), Translation);

			// glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1, 0, 0 });
			// rotation = glm::rotate(rotation, Rotation.y, { 0, 1, 0 });
			// rotation = glm::rotate(rotation, Rotation.z, { 0, 0, 1 });

			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			glm::mat4 scale = glm::scale(glm::mat4(1.0f), Scale);

			return translation * rotation * scale;
		}

		glm::mat4 GetWorldTransform() const
		{
			glm::mat4 translation = glm::translate(glm::mat4(1.0f), WorldTranslation);

			glm::mat4 rotation = glm::toMat4(glm::quat(WorldRotation));

			glm::mat4 scale = glm::scale(glm::mat4(1.0f), WorldScale);

			return translation * rotation * scale;
		}
	};

	// struct DefaultCubeComponent
	// {
	// 	glm::vec4 Color = { 0.8f, 0.2f, 0.3f, 1.0f };

	// 	//TODO: Implement Material / MaterialInstance
	// 	// Material = Shader + data/uniforms
	// 	// Ref<Material> Material = nullptr;
	// };

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; // TODO: implement in scene maybe?
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		// CameraComponent(const glm::mat4& projection)
			// : Camera(projection) {}
	};


	struct DefaultMaterialComponent
	{
		// Material Material;
		Ref<Rndr::Material> Material;
	};

	struct QuadComponent
	{
		glm::vec4 Color = { 0.8f, 0.2f, 0.3f, 1.0f };
	};

	struct CubeComponent
	{
		glm::vec4 Color = { 0.8f, 0.2f, 0.3f, 1.0f };
		// float sizeX = 1.0f, sizeY = 1.0f, sizeZ = 1.0f;
		glm::vec3 Size = { 1.0f, 1.0f, 1.0f };
	};

	struct TriComponent
	{
		glm::vec4 Color = { 0.8f, 0.2f, 0.3f, 1.0f };
	};

	struct NullComponent
	{
		bool Null = true;
	};


	struct MeshComponent
	{
		Ref<Rndr::Mesh> Mesh = CreateRef<Rndr::Mesh>();
		Ref<Rndr::Material> Material = CreateRef<Rndr::Material>();

		glm::vec3 Min = glm::vec3(FLT_MAX);
		glm::vec3 Max = glm::vec3(-FLT_MAX);
	};

}