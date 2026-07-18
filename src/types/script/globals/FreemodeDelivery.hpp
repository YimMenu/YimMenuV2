#pragma once
#include "types/script/types.hpp"
#include "types/script/Timer.hpp"

struct DeliveryPosData
{
	SCR_VEC3 DeliveryPosition1;
	SCR_VEC3 DeliveryPosition2;
};
static_assert(sizeof(DeliveryPosData) == 6 * 8);

struct FreemodeDelivery
{
	SCR_INT DeliveryFlags; // 0
	SCR_ARRAY<DeliveryPosData, 1011> DeliveryPosData; // 1
	SCR_BOOL DeliveryInVehicle; // 6068
	SCR_BOOL DeliveryNotInVehicle; // 6069
	TIMER DeliveryCooldown1; // 6070
	SCR_INT CooldownFrameCount1; // 6072
	TIMER DeliveryCooldown2; // 6073
	SCR_INT CooldownFrameCount2; // 6075

	static FreemodeDelivery* Get();
};
//static_assert(sizeof(FreemodeDelivery) == 6278 * 8);