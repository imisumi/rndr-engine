#pragma once

#include <glm/glm.hpp>

#include "opengl/VertexArray.h"

namespace Rndr
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0, uint32_t baseIndex = 0, uint32_t baseVertex = 0) = 0;
		virtual void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount, float LineWidth = 1.0f) = 0;

		// virtual void SetLineWidth(float width) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}