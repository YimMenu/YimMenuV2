#pragma once

// https://github.com/Lightning-X/Aera/blob/a8243421fe4f3f1f2a0583e625a916eedeca0272/Aera/src/rage/classes.h#L2140 
class CNetShopTransaction
{
public:
	virtual ~CNetShopTransaction() = 0;

	int m_TransactionId;      // 0x08
	int m_Type;               // 0x0C (basket vs service)
	char pad_0010[8];         // 0x10
	int m_Category;           // 0x18
	int m_Status;             // 0x1C
	char pad_0020[4];         // 0x20
	int m_Action;             // 0x24
	int m_Flags;              // 0x28
	bool m_Running;           // 0x2C
	// ...
};