#pragma once

#include "engine/system/MHCore.hpp"

namespace MHelmet 
{
	//namespace BUFFER
	//{
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
			case MHelmet::DataType::Float:  return 4;
			case MHelmet::DataType::Float2:	return 4 * 2;
			case MHelmet::DataType::Float3:	return 4 * 3;
			case MHelmet::DataType::Float4:	return 4 * 4;
			case MHelmet::DataType::Int:	return 4;
			case MHelmet::DataType::Int2:	return 4 * 2;
			case MHelmet::DataType::Int3:	return 4 * 3;
			case MHelmet::DataType::Int4:	return 4 * 4;
			case MHelmet::DataType::Mat3:	return 4 * 3 * 3;
			case MHelmet::DataType::Mat4:	return 4 * 4 * 4;
			case MHelmet::DataType::Bool:	return 1;
			
			}
			// mensaje de error en caso de no conocer el tipo
			return 0;
		}

		struct Element
		{
			Element() = default;

			std::string Name;
			DataType Type;
			uint32_t Offset;
			uint32_t Size;
			bool Normalized;
		

			Element(DataType type, const std::string& name, bool normalized = false)
				:Name(name), Type(type), Size(DataTypeSize(type)), Normalized(normalized), Offset(0)
			{}

			uint32_t ComponentCount() const
			{
				switch (Type)
				{
				case MHelmet::DataType::Float:  return 1;
				case MHelmet::DataType::Float2:	return 2;
				case MHelmet::DataType::Float3:	return 3;
				case MHelmet::DataType::Float4:	return 4;
				case MHelmet::DataType::Int:	return 1;
				case MHelmet::DataType::Int2:	return 2;
				case MHelmet::DataType::Int3:	return 3;
				case MHelmet::DataType::Int4:	return 4;
				case MHelmet::DataType::Mat3:	return 3 * 3;
				case MHelmet::DataType::Mat4:	return 4 * 4;
				case MHelmet::DataType::Bool:	return 1;

				}
				// mensaje de error o algun tipo de assert con DEBUG_BREAK
				return 0;
				
			}
		};

		struct Layout
		{
			Layout() = default;

			Layout(const std::initializer_list<Element>& elements) 
				: m_Elements(elements)
			{
				//m_Elements.reserve(10);
				CalculateOffsetAndStride();
			}

			inline uint32_t Stride() const { return m_Stride; }
			inline const std::vector<Element>& GetElements() const { return m_Elements; }
			
			inline const size_t GetNumberOfElements() const { return m_Elements.size(); }


			std::vector<Element>::iterator begin() { return m_Elements.begin(); }
			std::vector<Element>::iterator end()   { return m_Elements.end();   }
			
			
		private:

			void CalculateOffsetAndStride()
			{
				uint32_t offset = 0;
				m_Stride = 0;
				for (auto& element : m_Elements)
				{
					element.Offset = offset;
					offset   += element.Size;
					m_Stride += element.Size;
				}
			}
		private:
			std::vector<Element> m_Elements;
			uint32_t m_Stride = 0;
		};
	//}
}
