#include "netGameEvent.hpp"
#include "types/fx/ExplosionType.hpp"
#include "types/rage/datBitBuffer.hpp"

bool CScriptedGameEvent::Deserialize(rage::datBitBuffer& buffer)
{
	m_ArgsSize = buffer.Read<uint32_t>(32);

	if (m_ArgsSize > sizeof(m_Args))
		return false;

	buffer.ReadArrayBytes(m_Args, m_ArgsSize);
	return true;
}

void CNetworkIncrementStatEvent::Deserialize(rage::datBitBuffer& buffer)
{
	m_Stat = buffer.Read<uint32_t>(32);
	m_Amount = buffer.Read<uint32_t>(32, true);
}

void CDoorBreakEvent::Deserialize(rage::datBitBuffer& buffer)
{
	m_VehicleId = buffer.Read<uint16_t>(13);
	m_DoorId = buffer.Read<uint8_t>(3);
}

void CPlaySoundEvent::Deserialize(rage::datBitBuffer& buffer)
{
	m_IsEntity = buffer.Read<bool>(1);

	if (m_IsEntity)
	{
		m_EntityId = buffer.Read<uint16_t>(13);
	}
	else
	{
		m_Position = buffer.ReadPosition(19);
	}

	bool has_ref = buffer.Read<bool>(1);
	if (has_ref)
	{
		m_RefHash = buffer.Read<uint32_t>(32);
	}
	else
	{
		m_RefHash = 0;
	}

	m_SoundHash = buffer.Read<uint32_t>(32);
	m_SoundId = buffer.Read<uint8_t>(8);

	bool has_script_hash = buffer.Read<bool>(1);
	if (has_script_hash)
	{
		m_ScriptId.Deserialize(buffer);
	}
	else
	{
		m_ScriptId.m_Hash = 0;
	}
}

void CWeaponDamageEvent::Deserialize(rage::datBitBuffer& buffer)
{
	m_DamageType = buffer.Read<uint8_t>(2);
	m_WeaponType = buffer.Read<uint32_t>(32);
	m_OverrideDefaultDamage = buffer.Read<bool>(1);
	m_HitEntityWeapon = buffer.Read<bool>(1);
	m_HitWeaponAmmoAttachment = buffer.Read<bool>(1);
	m_Silenced = buffer.Read<bool>(1);
	m_DamageFlags = buffer.Read<uint32_t>(25);

	bool hasActionResult = buffer.Read<bool>(1);
	if (hasActionResult)
	{
		m_ActionResultName = buffer.Read<uint32_t>(32);
		m_ActionResultId = buffer.Read<uint16_t>(16);
		m_0x6C
			= buffer.Read<uint32_t>(32);
	}

	if (m_OverrideDefaultDamage)
	{
		m_WeaponDamage = buffer.Read<uint32_t>(17);
	}
	else
	{
		m_WeaponDamage = 0;
	}

	bool _f92 = buffer.Read<uint8_t>(1);
	if (_f92)
	{
		m_0x5C
			= buffer.Read<uint8_t>(5);
	}

	m_IsNetTargetPos = buffer.Read<uint8_t>(1);

	if (m_IsNetTargetPos)
	{
		m_LocalPos.x = buffer.ReadSignedFloat(16, 90.f);
		m_LocalPos.y = buffer.ReadSignedFloat(16, 90.f);
		m_LocalPos.z = buffer.ReadSignedFloat(16, 90.f);
	}

	if (m_DamageType == 3)
	{
		m_DamageTime = buffer.Read<uint32_t>(32);
		m_WillKill = buffer.Read<bool>(1);

		if (hasActionResult)
		{
			m_HitGlobalId = buffer.Read<uint16_t>(13);
		}
		else
		{
			m_HitGlobalId = 0;
		}

		bool f112 = buffer.Read<bool>(1);
		if (f112)
		{
			m_0x74
				= buffer.Read<uint16_t>(16);
		}
		else
		{
			m_0x74
				= buffer.Read<uint16_t>(11);
		}
	}
	else
	{
		m_ParentGlobalId = buffer.Read<uint16_t>(13);
		m_HitGlobalId = buffer.Read<uint16_t>(13);
	}

	if (m_DamageType < 2)
	{
		m_LocalPos.x = buffer.ReadSignedFloat(16, 90.f);
		m_LocalPos.y = buffer.ReadSignedFloat(16, 90.f);
		m_LocalPos.z = buffer.ReadSignedFloat(16, 90.f);

		if (m_DamageType == 1)
		{
			bool hasVehicleData = buffer.Read<bool>(1);

			if (hasVehicleData)
			{
				m_TyreIndex = buffer.Read<uint8_t>(4);
				m_SuspensionIndex = buffer.Read<uint8_t>(4);
			}
		}
	}
	else
	{
		m_HitComponent = buffer.Read<int>(5);
	}

	m_0x89
		= buffer.Read<bool>(1);
		m_HasImpactDir = buffer.Read<bool>(1);

		if (m_HasImpactDir)
		{
			m_ImpactDir.x = buffer.ReadSignedFloat(16, 6.2831855f);
			m_ImpactDir.y = buffer.ReadSignedFloat(16, 6.2831855f);
			m_ImpactDir.z = buffer.ReadSignedFloat(16, 6.2831855f);
		}
}

void CActivateVehicleSpecialAbilityEvent::Deserialize(rage::datBitBuffer& buffer)
{
	m_VehicleId = buffer.Read<uint16_t>(13);
	m_AbilityType = buffer.Read<uint32_t>(3);
}

void CExplosionEvent::Deserialize(rage::datBitBuffer& buffer)
{
	m_0xBA
		= buffer.Read<uint16_t>(16);
		m_TargetEntity = buffer.Read<uint16_t>(13);
		m_OwnerNetId = buffer.Read<uint16_t>(13);
		m_UnkNetId = buffer.Read<uint16_t>(13);
		m_ExplosionType = buffer.Read<ExplosionType>(8, true);
		m_DamageScale = buffer.ReadFloat(8, 1.0f);
		m_Position = buffer.ReadPosition(22);
		m_0xF2
			= buffer.Read<bool>(1);
			m_0x68
				= buffer.Read<uint32_t>(16);
				m_CameraShake = buffer.ReadSignedFloat(8, 1.0f);
				m_IsAudible = buffer.Read<bool>(1);
				m_0xBD
					= buffer.Read<bool>(1);
					m_IsInvisible = buffer.Read<bool>(1);
					m_0x7E
						= buffer.Read<bool>(1);
						m_AddOwnedExplosion = buffer.Read<bool>(1);
						m_0xF1
							= buffer.Read<bool>(1);
							m_HasTargetEnt2 = buffer.Read<bool>(1);
							m_TargetEnt2 = buffer.Read<uint16_t>(13);
							m_0x80
								= buffer.ReadVector3(16, 1.1f);
								m_0xBE
									= buffer.Read<bool>(1);
									m_0xBF
										= buffer.Read<bool>(1);
										m_0xA4
											= buffer.Read<uint32_t>(32);
											m_InteriorIndex = buffer.Read<uint32_t>(32);

											if (m_0xF2)
											{
												m_PositionUnk = buffer.ReadPosition(31);
											}

											m_0xF0
												= buffer.Read<bool>(1);

												if (m_AddOwnedExplosion)
												{
													m_ScriptHash = buffer.Read<uint32_t>(32);
													m_ProgramCounter = buffer.Read<uint32_t>(32);
												}

												if (m_0xF0)
												{
													m_0xDA
														= buffer.Read<uint16_t>(16);

														if (m_0xBF)
														{
															m_0xD8
																= buffer.Read<uint8_t>(8);
														}
												}
}

void CUpdateFxnEvent::Deserialize(rage::datBitBuffer& buffer)
{
	m_0x30
		= buffer.Read<uint32_t>(32);
		m_0x34
			= buffer.Read<uint32_t>(32);
}

void CRagdollRequestEvent::Deserialize(rage::datBitBuffer& buffer)
{
	m_PedToRagdoll = buffer.Read<uint16_t>(13);
}
