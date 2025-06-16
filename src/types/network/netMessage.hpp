#pragma once

namespace rage
{
	class netMessage
	{
	public:
		enum class Type
		{
			Invalid = 0xFFFFF,
			SessionAcceptChat = 0x62,
			StartMatchCmd = 0x2D,
			SetInvitableCmd = 0x1F,
			SessionMemberIds = 0x23,
			RequestGamerInfo = 0x54,
			RemoveGamersFromSessionCmd = 0x53,
			NotMigrating = 0x35,
			MigrateHostResponse = 0x12,
			MigrateHostRequest = 0x66,
			JoinResponse = 0x2A,
			JoinRequest = 0x41,
			HostLeftWhilstJoiningCmd = 0x58,
			ConfigResponse = 0x5F,
			ConfigRequest = 0x48,
			ChangeSessionAttributesCmd = 0x5A,
			AddGamerToSessionCmd = 0x64, // this is where send net info to lobby is called, among other things
			ReassignResponse = 0x10,
			ReassignNegotiate = 0x01,
			ReassignConfirm = 0x26,
			PlayerData = 0x18,
			PackedReliables = 0x30,
			PackedCloneSyncACKs = 0x3B,
			NonPhysicalData = 0x16,
			NetArrayMgrUpdateAck = 0x5D,
			NetArrayMgrUpdate = 0x60,
			NetArrayMgrSplitUpdateAck = 0x25,
			ScriptVerifyHostAck = 0x0B,
			ScriptVerifyHost = 0x3E,
			ScriptNewHost = 0x0E,
			ScriptMigrateHostFailAck = 0x1A,
			ScriptMigrateHost = 0x33,
			ScriptLeaveAck = 0x40,
			ScriptLeave = 0x17,
			ScriptJoinHostAck = 0x4D,
			ScriptJoinAck = 0x43,
			ScriptJoin = 0x5C,
			ScriptHostRequest = 0x67,
			ScriptHandshakeAck = 0x5B,
			ScriptHandshake = 0x57,
			ScriptBotLeave = 0x2B,        // unused?
			ScriptBotJoinAck = 0x63,      // unused?
			ScriptBotJoin = 0x1C,         // unused?
			ScriptBotHandshakeAck = 0x31, // unused?
			ScriptBotHandshake = 0x4B,    // unused?
			PartyLeaveGame = 0x3D,
			PartyEnterGame = 0x1E,
			CloneSync = 0x4E,          // aka clone_create, clone_sync etc.
			ActivateNetworkBot = 0x65, // unused?
			RequestObjectIds = 0x29,
			InformObjectIds = 0x09,
			TextMessage = 0x24, // this one is for chat
			PlayerIsTyping = 0x61,
			PackedEvents = 0x4F, // aka received_event
			PackedEventReliabless = 0x20,
			RequestKickFromHost = 0x0D,
			TransitionToGameStart = 0x50,
			TransitionToGameNotify = 0x02,
			TransitionToActivityStart = 0x06,
			TransitionToActivityFinish = 0x36,
			TransitionParameters = 0x3C,
			TransitionParameterString = 0x37,
			TransitionLaunchNotify = 0x1B,
			TransitionLaunch = 0x19,
			TransitionGamerInstruction = 0x14,
			TextMessage2 = 0x0A, // this one is for phone message
			SessionEstablishedRequest = 0x52,
			SessionEstablished = 0x07,
			RequestTransitionParameters = 0x42,
			RadioStationSyncRequest = 0x47,
			RadioStationSync = 0x46,
			PlayerCardSync = 0x3A,
			PlayerCardRequest = 0x6A,
			LostConnectionToHost = 0x81,
			KickPlayer = 0x34, // host kick
			DebugStall = 0x7E, // unused?
			CheckQueuedJoinRequestReply = 0x59,
			CheckQueuedJoinRequest = 0x51,
			Blacklist = 0x0C,
			RoamingRequestBubbleRequiredResponse = 0x83,
			RoamingRequestBubbleRequiredCheck = 0x82,
			RoamingRequestBubble = 0x2E,
			RoamingJoinBubble = 0x4C,
			RoamingJoinBubbleAck = 0x3F,
			RoamingInitialBubble = 0x32,
			VoiceStatus = 0x03,
			TextChatStatus = 0x00,
			JoinResponse2 = 0x08,
			JoinRequest2 = 0x68,
			NetTimeSync = 0x38,             // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 37
			NetComplaint = 0x55,            // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 54
			NetLagPing = 0x27,              // unused? ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 26
			SearchResponse = 0x6B,          // unused? ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 6A
			SearchRequest = 0x05,           // unused?
			QosProbeResponse = 0x2C,        // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 2B
			QosProbeRequest = 0x1D,         // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 1C
			CxnRelayAddressChanged = 0x49,  // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 48
			CxnRequestRemoteTimeout = 0x2F, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 2E
			SessionDetailRequest = 0x22,    // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 21
			SessionDetailResponse = 0x13,   // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 12
			KeyExchangeOffer = 0x0F,        // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 0E (last result)
			KeyExchangeAnswer = 0x44,       // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 43
			_0x87 = 0x87,
			_0x88 = 0x88,
			_0x80 = 0x80,
			_0x28 = 0x28,
			_0x11 = 0x11,
			_0x45 = 0x45,
			_0x89 = 0x89,
			_0x86 = 0x86,
			BattlEyeCmd = 0x8F,
		};
	};
}