#pragma once
#include "scrVector.hpp"

#include <cstdint>

#ifndef BOOL
	#define BOOL int
#endif

using Void = void;
using Any = int;
using Hash = std::uint32_t;
using Entity = std::int32_t;
using Player = std::int32_t;
using FireId = std::int32_t;
using Interior = std::int32_t;
using Ped = Entity;
using Vehicle = Entity;
using Cam = std::int32_t;
using Object = Entity;
using Pickup = Object;
using Blip = std::int32_t;
using Camera = Entity;
using ScrHandle = Entity;
using Vector3 = rage::scrVector;

#define PLAYER_INDEX alignas(8) Player
#define ENTITY_INDEX alignas(8) Entity
#define PED_INDEX alignas(8) Ped
#define VEHICLE_INDEX alignas(8) Vehicle
#define INTERIOR_INDEX alignas(8) Interior
#define BLIP_INDEX alignas(8) Blip
#define NETWORK_INDEX alignas(8) int

#define SCR_SIZEOF(x) (sizeof(x) / 8)
#define SCR_HASH alignas(8) Hash
#define SCR_INT alignas(8) int
#define SCR_BOOL alignas(8) BOOL
#define SCR_FLOAT alignas(8) float
#define SCR_VEC3 Vector3

template<int SIZE>
struct SCR_TEXT_LABEL
{
	alignas(8) char Data[SIZE];

private:
	alignas(8) char _PAD[SIZE];

public:
	operator char*()
	{
		return Data;
	}
};

#define TEXT_LABEL_15 SCR_TEXT_LABEL<16>
#define TEXT_LABEL_23 SCR_TEXT_LABEL<24>
#define TEXT_LABEL_31 SCR_TEXT_LABEL<32>
#define TEXT_LABEL_63 SCR_TEXT_LABEL<64>

template<typename T, int SIZE>
struct SCR_ARRAY
{
	SCR_INT Size;
	alignas(8) T Data[SIZE];

	T& operator[](int index)
	{
		return Data[index];
	}
};

template<typename T>
struct SCR_BITSET
{
	alignas(8) int Value;

	bool IsSet(T val)
	{
		return Value & (1 << (int)val);
	}

	void Set(T val)
	{
		Value |= (1 << (int)val);
	}

	void Clear(T val)
	{
		Value &= ~(1 << (int)val);
	}
};

struct Color3
{
	SCR_INT R;
	SCR_INT G;
	SCR_INT B;
};
static_assert(sizeof(Color3) == 3 * 8);

struct Date
{
	SCR_INT Year, Month, Day, Hour, Minute, Second, Millisecond;
};
static_assert(sizeof(Date) == 7 * 8);

// serialized bitbuffer data of rage::rlGamerHandle + some padding for last gen compatibility
// TODO: is the above statement true in Enhanced?
// seemingly yes
struct GAMER_HANDLE
{
private:
	uint64_t Data[13];
};
static_assert(sizeof(GAMER_HANDLE) == 13 * 8);

#define NUM_CONTACTS 86