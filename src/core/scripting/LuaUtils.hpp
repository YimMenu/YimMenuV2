#include "lua.hpp"
#include "core/util/Joaat.hpp"
#undef GetObject // another dumb Windows.h definition

namespace YimMenu::Lua
{
	template<typename T>
	class Metatable
	{
		inline static int m_Index;
		inline static std::vector<int> m_Subclasses;

	public:
		static inline void Register(lua_State* state)
		{
			m_Index = luaL_ref(state, LUA_REGISTRYINDEX);
		}

		static inline int Get()
		{
			return m_Index;
		}

		static inline const std::vector<int>& GetSubclasses()
		{
			return m_Subclasses;
		}

		template<typename T2>
		static inline void AddSubclass()
		{
			m_Subclasses.push_back(Metatable<T2>::Get());
		}
	};

	// Tries to get the userdata or errors out
	template <typename T>
	inline T& GetObject(lua_State* state, int idx)
	{
		auto data = lua_touserdata(state, idx);
		if (!data)
			luaL_argerror(state, idx, "cannot get userdata at this index");

		if (!lua_getmetatable(state, idx))
			luaL_argerror(state, idx, "cannot get metatable for the userdata at this index");

		lua_rawgeti(state, LUA_REGISTRYINDEX, Metatable<T>::Get());
		auto equals = lua_rawequal(state, -1, -2);
		lua_pop(state, 1);

		if (equals)
		{
			lua_pop(state, 1);
			return *reinterpret_cast<T*>(data);
		}

		const auto& subclasses = Metatable<T>::GetSubclasses();
		if (!equals && subclasses.size())
		{
			for (const auto subclass : subclasses)
			{
				lua_rawgeti(state, LUA_REGISTRYINDEX, subclass);
				auto equals = lua_rawequal(state, -1, -2);
				lua_pop(state, 1);

				if (equals)
				{
					lua_pop(state, 1);
					return *reinterpret_cast<T*>(data);
				}
			}
		}

		lua_pop(state, 1);
		luaL_argerror(state, idx, "the metatable for this userdata at this index is incorrect");
		std::unreachable();
	}

	inline void SetFunction(lua_State* state, lua_CFunction func, const char* name)
	{
		lua_pushcfunction(state, func);
		lua_setfield(state, -2, name);
	}

	// This is a terrible hack
	template<lua_CFunction actual_func>
	inline int DropSelf(lua_State* state)
	{
		lua_remove(state, 1);
		return actual_func(state);
	}

	// Requires your table to be at the top of stack
	// Creates a metatable for the table, which might not desirable
	template<lua_CFunction ctor>
	inline void SetConstructor(lua_State* state)
	{
		SetFunction(state, ctor, "new");

		lua_newtable(state);
		SetFunction(state, DropSelf<ctor>, "__call");
		lua_setmetatable(state, -2);
	}

	// Creates an object and pushes it on the stack
	template<typename T, class... Args>
	inline T* CreateObject(lua_State* state, Args&& ...args)
	{
		void* data = lua_newuserdata(state, sizeof(T));
		new (data) T(std::forward<Args>(args)...); // construct in-place
		lua_rawgeti(state, LUA_REGISTRYINDEX, Metatable<T>::Get());
		lua_setmetatable(state, -2);
		return reinterpret_cast<T*>(data);
	}

	// Copies an existing object and pushes it on the stack
	// A copy ctor must be defined or something like that
	template<typename T, class... Args>
	inline T* CopyObject(lua_State* state, const T& existing)
	{
		void* data = lua_newuserdata(state, sizeof(T));
		*reinterpret_cast<T*>(data) = existing;
		lua_rawgeti(state, LUA_REGISTRYINDEX, Metatable<T>::Get());
		lua_setmetatable(state, -2);
		return reinterpret_cast<T*>(data);
	}

	// Moves an existing object and pushes it on the stack
	// A move ctor must be defined or something like that
	template<typename T, class... Args>
	inline T* MoveObject(lua_State* state, T&& existing)
	{
		void* data = lua_newuserdata(state, sizeof(T));
		*reinterpret_cast<T*>(data) = std::move(existing);
		lua_rawgeti(state, LUA_REGISTRYINDEX, Metatable<T>::Get());
		lua_setmetatable(state, -2);
		return reinterpret_cast<T*>(data);
	}

	inline std::uint32_t GetHashArgument(lua_State* state, int index)
	{
		if (lua_type(state, index) == LUA_TSTRING)
			return Joaat(lua_tostring(state, index));
		else
			return luaL_checkinteger(state, index);
	}

	// luaL_checkstring automatically converts ints into strings, which we don't want
	inline const char* CheckStringSafe(lua_State* state, int index, size_t* size = nullptr)
	{
		luaL_checktype(state, index, LUA_TSTRING);
		return lua_tolstring(state, index, size);
	}

	// lua doesn't even offer a check function for bools
	inline bool CheckBooleanSafe(lua_State* state, int index)
	{
		luaL_checktype(state, index, LUA_TBOOLEAN);
		return lua_toboolean(state, index);
	}
}