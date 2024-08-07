#pragma once

#include "RendererAPI.h"

namespace Rndr
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0, uint32_t baseIndex = 0, uint32_t baseVertex = 0)
		{
			s_RendererAPI->DrawIndexed(vertexArray, indexCount, baseIndex, baseVertex);
		}

		inline static void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount, float lineWidth = 1.0f)
		{
			s_RendererAPI->DrawLines(vertexArray, vertexCount, lineWidth);
		}

		// inline static void SetLineWidth(float width)
		// {
		// 	s_RendererAPI->SetLineWidth(width);
		// }
	private:
		static RendererAPI* s_RendererAPI;
	};
}