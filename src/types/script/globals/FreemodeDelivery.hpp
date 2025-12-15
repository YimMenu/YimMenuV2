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
	SCR_ARRAY<DeliveryPosData, 1008> DeliveryPosData; // 1
	SCR_BOOL DeliveryInVehicle; // 6050
	SCR_BOOL DeliveryNotInVehicle; // 6051
	TIMER DeliveryCooldown1; // 6052
	SCR_INT CooldownFrameCount1; // 6054
	TIMER DeliveryCooldown2; // 6055
	SCR_INT CooldownFrameCount2; // 6057

	static FreemodeDelivery* Get();
};
//static_assert(sizeof(FreemodeDelivery) == 6260 * 8);