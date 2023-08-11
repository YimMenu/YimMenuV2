#pragma once
#include "Pattern.hpp"
#include "PointerCalculator.hpp"

#include <functional>
#include <vector>

namespace YimMenu
{
	class Module;
	using PatternFunc = std::function<void(PointerCalculator)>;

	class PatternScanner
	{
	private:
		const Module* m_Module;
		std::vector<std::pair<const IPattern*, PatternFunc>> m_Patterns;

	public:
		PatternScanner(const Module* module);

		template<Signature S>
		void Add(const Pattern<S>& pattern, const PatternFunc& func);
		bool Scan();

	private:
		bool ScanInternal(const IPattern* pattern, PatternFunc func) const;
	};

	template<Signature S>
	inline void PatternScanner::Add(const Pattern<S>& pattern, const PatternFunc& func)
	{
		m_Patterns.push_back(std::move(std::make_pair(&pattern, func)));
	}
}
