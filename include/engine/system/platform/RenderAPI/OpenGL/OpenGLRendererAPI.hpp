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

		virtual void Draw(const RefCount<VAO>& _VAO) override;

	

	};
}