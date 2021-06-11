#pragma once

#include "engine/system/MHCore.hpp"

namespace MHelmet 
{
	namespace SHADER
	{
		enum class DataType
		{
			None = 0,
			Float, Float2, Float3, Float4,
			Int, Int2, Int3, Int4,
			Mat3, Mat4,
			Bool
		};

		static uint32_t DataTypeSize(DataType type)
		{
			switch (type)
			{
			case MHelmet::SHADER::DataType::Float:  return 4;
			case MHelmet::SHADER::DataType::Float2:	return 4 * 2;
			case MHelmet::SHADER::DataType::Float3:	return 4 * 3;
			case MHelmet::SHADER::DataType::Float4:	return 4 * 4;
			case MHelmet::SHADER::DataType::Int:	return 4;
			case MHelmet::SHADER::DataType::Int2:	return 4 * 2;
			case MHelmet::SHADER::DataType::Int3:	return 4 * 3;
			case MHelmet::SHADER::DataType::Int4:	return 4 * 4;
			case MHelmet::SHADER::DataType::Mat3:	return 4 * 3 * 3;
			case MHelmet::SHADER::DataType::Mat4:	return 4 * 4 * 4;
			case MHelmet::SHADER::DataType::Bool:	return 1;
			
			}
			// mensaje de error en caso de no conocer el tipo
			return 0;
		}

		struct Element
		{
			std::string Name;
			DataType Type;
			uint32_t Offset = 0;
			uint32_t Size;

			Element(DataType type, const std::string& name)
				:Name(name), Type(DataType(type)) {}
		};

		struct Layout
		{
			Layout(const std::initializer_list<Element>& elements) 
				: m_Elements(elements)
			{
				CalculateOffsetAndStride();
			}

			inline const std::vector<Element>& GetElements() const
			{
				return m_Elements;
			}
		private:
			void CalculateOffsetAndStride()
			{
				uint32_t offset = 0;
				m_Stride = 0;
				for (auto& element : m_Elements)
				{
					element.Name = offset;
					offset   += element.Size;
					m_Stride += element.Offset;
				}
			}
		private:
			std::vector<Element> m_Elements;
			uint32_t m_Stride = 0;
		};
	}
}
