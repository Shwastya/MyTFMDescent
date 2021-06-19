#pragma once
#include "engine/system/MHCore.hpp"

#include "engine/system/renderer/RendererApi.hpp"

namespace MHelmet
{
	class OpenGlRendererAPI : public RendererAPI
	{
	public:

		virtual void Init() override;

		virtual void ClearColor(const glm::vec4& color) override;

		virtual void clear() override;

		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t w, uint32_t h) override;

		virtual void Draw(const RefCount<VAO>& _VAO) override;

	

	};
}