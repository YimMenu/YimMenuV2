#pragma once

class sStatData
{
public:
	enum class Type
	{
		INT = 1,
		FLOAT,
		STRING,
		_BOOL,
		UINT8,
		UINT16,
		UINT32,
		UINT64,
		DATE = 20,
		POS,
		INT64 = 26,
	};

	// it isn't recommended to call the SetXXX() functions directly, use the natives instead
	virtual ~sStatData() = default;                     // 0x00
	virtual void Reset() = 0;                           // 0x08
	virtual void SetInt(int value) = 0;                 // 0x10
	virtual void SetInt64(std::int64_t value) = 0;      // 0x18
	virtual void SetFloat(float value) = 0;             // 0x20
	virtual void SetBool(bool value) = 0;               // 0x28
	virtual void SetUInt8(std::uint8_t value) = 0;      // 0x30
	virtual void SetUInt16(std::uint16_t value) = 0;    // 0x38
	virtual void SetUInt32(std::uint32_t value) = 0;    // 0x40
	virtual void SetUInt64(std::uint64_t value) = 0;    // 0x48
	virtual void SetString(const char* value) = 0;      // 0x50
	virtual bool SetUserID(const char* value) = 0;      // 0x58
	virtual int GetInt() = 0;                           // 0x60
	virtual std::int64_t GetInt64() = 0;                // 0x68
	virtual float GetFloat() = 0;                       // 0x70
	virtual bool GetBool() = 0;                         // 0x78
	virtual std::uint8_t GetUInt8() = 0;                // 0x80
	virtual std::uint16_t GetUInt16() = 0;              // 0x88
	virtual std::uint32_t GetUInt32() = 0;              // 0x90
	virtual std::uint64_t GetUInt64() = 0;              // 0x98
	virtual const char* GetString() = 0;                // 0xA0
	virtual bool GetUserID(char* buffer, int size) = 0; // 0xA8
	virtual bool GetProfileSetting(void* buffer) = 0;   // 0xB0
	virtual bool IsEqual(std::uint64_t* value) = 0;     // 0xB8
	virtual Type GetType() = 0;                         // 0xC0
	virtual const char* GetTypeString() = 0;            // 0xC8
	virtual int GetSize() = 0;                          // 0xD0
	virtual bool IsObfuscated() = 0;                    // 0xD8
	virtual void UnkE0(bool unk) = 0;                   // 0xE0
	virtual int UnkE8() = 0;                            // 0xE8
	virtual bool IsValueNull() = 0;                     // 0xF0

	uint32_t m_Flags;

	inline bool IsServerAuthoritative() const
	{
		return (m_Flags & 0x80) != 0;
	}

	inline bool IsControlledByNetshop() const
	{
		return (m_Flags & 0x8000000) != 0;
	}
};
static_assert(sizeof(sStatData) == 0x10);

struct sStatMap
{
	uint32_t m_Hash;
	uint32_t m_Unk;
	sStatData* m_Data;
};
static_assert(sizeof(sStatMap) == 0x10);
