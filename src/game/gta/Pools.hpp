#pragma once
#include "Entity.hpp"
#include "Ped.hpp"
#include "Vehicle.hpp"

#include "types/rage/fwBasePool.hpp"
#include "types/vehicle/fwVehiclePool.hpp"


namespace YimMenu
{
	rage::fwBasePool* GetPedPool();
	rage::fwBasePool* GetObjectPool();
	rage::fwVehiclePool* GetVehiclePool();

	template<typename Wrapper, typename PoolType>
	class PoolIterator
	{
	public:
		PoolType* m_Pool = nullptr;
		uint32_t m_Index = 0;

		explicit PoolIterator(PoolType* pool, int32_t index = 0)
		{
			this->m_Pool = pool;
			this->m_Index = index;
		}

		PoolIterator& operator++()
		{
			for (m_Index++; m_Index < m_Pool->m_Size; m_Index++)
			{
				if (m_Pool->IsValid(m_Index))
				{
					return *this;
				}
			}

			m_Index = m_Pool->m_Size;
			return *this;
		}

		Wrapper operator*()
		{
			auto addr = reinterpret_cast<void*>(m_Pool->GetAt(m_Index));
			return Wrapper(addr);
		}

		bool operator!=(const PoolIterator& other) const
		{
			return this->m_Index != other.m_Index;
		}
	};

	// Common functions for VehiclePool and GenericPool
	template<typename Wrapper, typename PoolType>
	class PoolUtils
	{
		PoolType* m_Pool;

	public:
		PoolUtils(PoolType* pool) :
		    m_Pool(pool)
		{
		}

		auto begin()
		{
			return ++PoolIterator<Wrapper, PoolType>(m_Pool, -1);
		}

		auto end()
		{
			return ++PoolIterator<Wrapper, PoolType>(m_Pool, m_Pool->m_Size);
		}

		auto size()
		{
			return m_Pool->m_Size;
		}
	};

	namespace Pools
	{
		inline PoolUtils<Ped, rage::fwBasePool> GetPeds()
		{
			return PoolUtils<Ped, rage::fwBasePool>(GetPedPool());
		}

		inline PoolUtils<Entity, rage::fwBasePool> GetObjects()
		{
			return PoolUtils<Entity, rage::fwBasePool>(GetObjectPool());
		}

		inline PoolUtils<Vehicle, rage::fwVehiclePool> GetVehicles()
		{
			return PoolUtils<Vehicle, rage::fwVehiclePool>(GetVehiclePool());
		}
	}
}