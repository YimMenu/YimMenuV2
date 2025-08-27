#pragma once
#include "core/util/Joaat.hpp"

namespace YimMenu
{
	using CustomLabelText_t = std::function<const char*(const char*)>;
	class CustomLabelText
	{
		static CustomLabelText& GetInstance()
		{
			static CustomLabelText instance;
			return instance;
		}
	public:
		static uint64_t ComputeHash(const char* str)
		{
			return Joaat(str);
		}
		static uint64_t ComputeHash(uint64_t value)
		{
			return value;
		}

		static void Init()
		{
			return GetInstance().InitImpl();
		}

		static bool AddLabel(joaat_t hash, const std::string_view text)
		{
			return GetInstance().AddLabelImpl(hash, text);
		}

		static bool AddLabel(joaat_t hash, CustomLabelText_t&& cb)
		{
			return GetInstance().AddLabelImpl(hash, std::move(cb));
		}

		template<typename T>
		static const char* GetText(const T& label)
		{
			return GetInstance().GetTextImpl(label);
		}
	private:
		bool AddLabelImpl(joaat_t hash, const std::string_view text);
		bool AddLabelImpl(joaat_t hash, CustomLabelText_t&& cb);

		void InitImpl();

		 template<typename T>
		const char* GetTextImpl(const T& label) const
		{
			uint64_t hash;

			if constexpr (std::is_same_v<T, const char*>)
				hash = ComputeHash(label);
			else if constexpr (std::is_same_v<T, uint32_t>)
				hash = ComputeHash(label);
			else
				static_assert(sizeof(T) == 0, "Label type Unsupported");

			if (const auto& it = m_Labels.find(hash); it != m_Labels.end())
			{
				if constexpr (std::is_same_v<T, const char*>)
					return it->second(label);
				else
					return it->second(nullptr);
			}

			if (const auto& it = m_LabelOverwrites.find(hash); it != m_LabelOverwrites.end())
				return it->second.get();

			return nullptr;
		}

		std::unordered_map<uint64_t, std::function<const char*(const char*)>> m_Labels;
		std::unordered_map<joaat_t, std::unique_ptr<char[]>> m_LabelOverwrites;
	};
}