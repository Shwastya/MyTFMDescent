//#pragma once
//#include <glm/glm.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/constants.hpp>
//
//#include <glad/glad.h>
//
//#include "engine/system/renderer/PerspectiveCamera.hpp";
//#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"
//
//
//namespace MHelmet
//{
//	struct ParticleProps
//	{
//		glm::vec2 Position;
//		glm::vec2 Velocity, VelocityVariation;
//		glm::vec4 ColorBegin, ColorEnd;
//		float SizeBegin, SizeEnd, SizeVariation;
//		float LifeTime = 1.0f;
//	};
//
//	class ParticleSystem
//	{
//	public:
//		ParticleSystem();
//
//		void OnUpdate(DeltaTime ts);
//		void OnRender(PerspectiveCamera& camera);
//
//		void Emit(const ParticleProps& particleProps);
//	private:
//		struct Particle
//		{
//			glm::vec2 Position;
//			glm::vec2 Velocity;
//			glm::vec4 ColorBegin, ColorEnd;
//			float Rotation = 0.0f;
//			float SizeBegin, SizeEnd;
//
//			float LifeTime = 1.0f;
//			float LifeRemaining = 0.0f;
//
//			bool Active = false;
//		};
//		std::vector<Particle> m_ParticlePool;
//		uint32_t m_PoolIndex = 999;
//	};
//}