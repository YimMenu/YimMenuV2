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
	SCR_ARRAY<DeliveryPosData, 1004> DeliveryPosData; // 1
	SCR_BOOL DeliveryInVehicle; // 6026
	SCR_BOOL DeliveryNotInVehicle; // 6027
	TIMER DeliveryCooldown1; // 6028
	SCR_INT CooldownFrameCount1; // 6030
	TIMER DeliveryCooldown2; // 6031
	SCR_INT CooldownFrameCount2; // 6033

	static FreemodeDelivery* Get();
};
//static_assert(sizeof(FreemodeDelivery) == 6237 * 8);