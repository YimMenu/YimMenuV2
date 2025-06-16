#pragma once
#include "PatternHash.hpp"
#include "core/util/StrToHex.hpp"

#include <string_view>
#include <vector>

namespace YimMenu
{
	template<std::size_t N>
	struct Signature
	{
		char m_Signature[N]{};
		std::size_t m_SignatureByteLength;
		PatternHash m_Hash;

		constexpr Signature(char const (&signature)[N]) :
		    m_SignatureByteLength(0)
		{
			std::ranges::copy(signature, m_Signature);

			for (std::size_t i = 0; i < N; i++)
			{
				m_Hash = m_Hash.Update(m_Signature[i]);
				if (m_Signature[i] == ' ' || m_Signature[i] == '\0')
					m_SignatureByteLength++;
			}

			m_Hash = m_Hash.Update(m_SignatureByteLength);
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

		constexpr PatternHash Hash() const
		{
			return m_Hash;
		}
	};

	class IPattern
	{
	public:
		constexpr IPattern() = default;
		virtual ~IPattern() = default;

		virtual const std::string_view Name() const = 0;
		virtual constexpr std::span<const std::optional<std::uint8_t>> Signature() const = 0;
		virtual const PatternHash Hash() const = 0;
	};

	template<Signature S>
	class Pattern final : public IPattern
	{
	private:
		const std::string_view m_Name;
		std::array<std::optional<std::uint8_t>, S.ByteLength()> m_Signature;
		PatternHash m_Hash;

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
		inline virtual const PatternHash Hash() const override
		{
			return m_Hash;
		}
	};

	template<Signature S>
	inline constexpr Pattern<S>::Pattern(const std::string_view name) :
	    IPattern(),
	    m_Name(name)
	{
		m_Hash = S.Hash();

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

			int next = i + 1;
			m_Signature[pos++] = static_cast<std::uint8_t>(StrToHex(S.Get()[i]) * 0x10 + StrToHex(S.Get()[next]));
			i++;
		}
	}

	class SimplePattern
	{
	public:
		SimplePattern(std::string_view ida_sig);
		inline SimplePattern(const char* ida_sig) :
		    SimplePattern(std::string_view(ida_sig))
		{
		}

		inline SimplePattern(SimplePattern&& other) :
		    m_Bytes(other.m_Bytes)
		{
		}

		inline SimplePattern(const SimplePattern& other) :
		    m_Bytes(other.m_Bytes)
		{
		}

		std::vector<std::optional<uint8_t>> m_Bytes;
	};
}