#pragma once
#include "util/StrToHex.hpp"

#include <string_view>

namespace YimMenu
{
	template<std::size_t N>
	struct Signature
	{
		char m_Signature[N]{};
		std::size_t m_SignatureByteLength;

		constexpr Signature(char const (&signature)[N]) :
		    m_SignatureByteLength(0)
		{
			std::ranges::copy(signature, m_Signature);

			for (std::size_t i = 0; i < N; i++)
			{
				if (m_Signature[i] == ' ' || m_Signature[i] == '\0')
					m_SignatureByteLength++;
			}
		}

		/**
		 * @brief Signature string
		 * 
		 * @return constexpr const decltype(m_Signature)& 
		 */
		inline constexpr const decltype(m_Signature)& Get() const
		{
			return m_Signature;
		}
		/**
		 * @brief Returns the Length of the original signature string
		 * 
		 * @return constexpr std::size_t 
		 */
		constexpr std::size_t Length() const
		{
			return N;
		}
		/**
		 * @brief Returns the actual length in bytes for the signature
		 * 
		 * @return constexpr std::size_t 
		 */
		constexpr std::size_t ByteLength() const
		{
			return m_SignatureByteLength;
		}
	};

	class IPattern
	{
	public:
		constexpr IPattern() = default;
		virtual ~IPattern()  = default;

		virtual const std::string_view Name() const                                      = 0;
		virtual constexpr std::span<const std::optional<std::uint8_t>> Signature() const = 0;
	};

	template<Signature S>
	class Pattern final : public IPattern
	{
	private:
		const std::string_view m_Name;
		std::array<std::optional<std::uint8_t>, S.ByteLength()> m_Signature;

	public:
		constexpr Pattern(const std::string_view name);

		inline virtual const std::string_view Name() const override
		{
			return m_Name;
		}
		inline virtual constexpr std::span<const std::optional<std::uint8_t>> Signature() const override
		{
			return m_Signature;
		}

		friend std::ostream& operator<< <>(std::ostream& os, const Pattern<S>& signature);
	};

	template<Signature S>
	inline constexpr Pattern<S>::Pattern(const std::string_view name) :
	    IPattern(),
	    m_Name(name)
	{
		for (size_t i = 0, pos = 0; i < S.Length(); i++)
		{
			const auto c = S.Get()[i];
			if (c == ' ')
				continue;
			if (c == '\0')
				break;

			if (S.Get()[i] == '?')
			{
				if (S.Get()[i + 1] == '?')
					i++;

				m_Signature[pos++] = std::nullopt;

				continue;
			}


			m_Signature[pos++] = static_cast<std::uint8_t>(StrToHex(S.Get()[i]) * 0x10 + StrToHex(S.Get()[++i]));
		}
	}

	template<Signature S>
	inline std::ostream& operator<<(std::ostream& os, const Pattern<S>& pattern)
	{
		os << pattern.Name() << ": { ";
		for (const auto byte : pattern.Signature())
		{
			if (byte == std::nullopt)
			{
				os << "?? ";
				continue;
			}
			os << std::hex << std::uppercase << DWORD64(byte.value()) << std::nouppercase << std::dec << ' ';
		}
		os << "}";
		return os;
	}
}