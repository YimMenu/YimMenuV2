#pragma once
#include <memory>
#include <span>
#include <vector>

namespace YimMenu
{
    template<typename T>
    concept SpanCompatibleType = requires(T a)
    {
        std::span{a};
    };

    class BytePatch
    {
    private:
        byte* m_Address;
        std::unique_ptr<byte[]> m_Patch;
        std::unique_ptr<byte[]> m_Original;
        std::size_t m_Size;

    protected:
        static inline std::vector<std::unique_ptr<BytePatch>> m_Patches;

    public:
        virtual ~BytePatch();

        void Apply() const;
        void Restore() const;
        void Remove() const;

        static void RestoreAll();

        template<typename TAddr>
        static const std::unique_ptr<BytePatch>& Make(TAddr addr, std::remove_pointer_t<std::remove_reference_t<TAddr>> value);

        template<typename TAddr, typename T>
        requires SpanCompatibleType<T>
        static const std::unique_ptr<BytePatch>& Make(TAddr addr, T spanCompatible);

    private:
        template<typename TAddr>
        BytePatch(TAddr addr, std::remove_pointer_t<std::remove_reference_t<TAddr>> value);

        template<typename TAddr, typename T, std::size_t N>
        BytePatch(TAddr addr, std::span<T, N> span);

        friend bool operator==(const std::unique_ptr<BytePatch>& a, const BytePatch* b);

    };

	template<typename TAddr>
	inline const std::unique_ptr<BytePatch>& BytePatch::Make(TAddr addr, std::remove_pointer_t<std::remove_reference_t<TAddr>> value)
	{
		return m_Patches.emplace_back(std::unique_ptr<BytePatch>(new BytePatch(addr, value)));
	}

	template<typename TAddr, typename T>
    requires SpanCompatibleType<T>
	inline const std::unique_ptr<BytePatch>& BytePatch::Make(TAddr addr, T spanCompatible)
	{
		return m_Patches.emplace_back(std::unique_ptr<BytePatch>(new BytePatch(addr, std::span{spanCompatible})));
	}
    
    template<typename TAddr>
    inline BytePatch::BytePatch(TAddr addr, std::remove_pointer_t<std::remove_reference_t<TAddr>> value) :
        m_Address(addr)
    {
        m_Size = sizeof(std::remove_pointer_t<std::remove_reference_t<TAddr>>);

        m_Original = std::make_unique<byte[]>(m_Size);
        std::copy_n(m_Address, m_Size, m_Original.get());

        m_Patch = std::make_unique<byte[]>(m_Size);
        std::copy_n(&value, m_Size, m_Patch.get());
    }

    template<typename TAddr, typename T, std::size_t N>
    inline BytePatch::BytePatch(TAddr addr, std::span<T, N> span) :
        m_Address((byte*)addr)
    {
        m_Size = span.size();

        m_Original = std::make_unique<byte[]>(m_Size);
        std::copy_n(m_Address, m_Size, m_Original.get());

        m_Patch = std::make_unique<byte[]>(m_Size);
        std::copy(span.begin(), span.end(), m_Patch.get());
    }
}