#pragma once

class CBattlEyeClient;
class CBattlEyeServer;
class CBattlEyePlayerModifyContext;

class CBattlEyePlayerModifyInterface
{
public:
	virtual ~CBattlEyePlayerModifyInterface() = default;
	virtual bool ProcessPlayerJoin(const CBattlEyePlayerModifyContext* context) = 0;
	virtual bool ProcessPlayerLeave(const CBattlEyePlayerModifyContext* context) = 0;

	CBattlEyeClient* m_Client;
	CBattlEyeServer* m_Server;
};
