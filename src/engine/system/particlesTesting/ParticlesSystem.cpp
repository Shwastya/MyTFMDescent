//#pragma once
//
//#include "engine/system/particlesTesting/ParticlesSystem.hpp"
//
//#include "engine/system/particlesTesting/Random.hpp"
//#include <glad/glad.h>
//
//
//#include <glm/gtx/compatibility.hpp>
//
//namespace MHelmet {
//
//	ParticleSystem::ParticleSystem()
//	{
//		m_ParticlePool.resize(1000);
//	}
//
//
//	void ParticleSystem::OnUpdate(DeltaTime ts)
//	{
//		for (auto& particle : m_ParticlePool)
//		{
//			if (!particle.Active)
//				continue;
//
//			if (particle.LifeRemaining <= 0.0f)
//			{
//				particle.Active = false;
//				continue;
//			}
//
//			particle.LifeRemaining -= ts.Seconds();
//			particle.Position += particle.Velocity * (float)ts.Seconds();
//			particle.Rotation += 0.01f * ts.Seconds();
//		}
//	}
//
//	void ParticleSystem::OnRender(PerspectiveCamera& camera)
//	{
//		
//		for (auto& particle : m_ParticlePool)
//		{
//			if (!particle.Active)
//				continue;
//
//			// Fade away particles
//			float life = particle.LifeRemaining / particle.LifeTime;
//			glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
//			//color.a = color.a * life;
//
//			float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);
//
//			// Render
//			glm::mat4 transform = glm::translate(glm::mat4(1.0f), { particle.Position.x, particle.Position.y, 0.0f })
//				* glm::rotate(glm::mat4(1.0f), particle.Rotation, { 0.0f, 0.0f, 1.0f })
//				* glm::scale(glm::mat4(1.0f), { size, size, 1.0f });
//	
//		}
//	}
//
//	void ParticleSystem::Emit(const ParticleProps& particleProps)
//	{
//		Particle& particle = m_ParticlePool[m_PoolIndex];
//		particle.Active = true;
//		particle.Position = particleProps.Position;
//		particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();
//
//		// Velocity
//		particle.Velocity = particleProps.Velocity;
//		particle.Velocity.x += particleProps.VelocityVariation.x * (Random::Float() - 0.5f);
//		particle.Velocity.y += particleProps.VelocityVariation.y * (Random::Float() - 0.5f);
//
//		// Color
//		particle.ColorBegin = particleProps.ColorBegin;
//		particle.ColorEnd = particleProps.ColorEnd;
//
//		particle.LifeTime = particleProps.LifeTime;
//		particle.LifeRemaining = particleProps.LifeTime;
//		particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (Random::Float() - 0.5f);
//		particle.SizeEnd = particleProps.SizeEnd;
//
//		m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
//	}
//}