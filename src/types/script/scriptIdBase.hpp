#pragma once
#include <cstdint>

namespace rage
{
	class datBitBuffer;
	class netLoggingInterface;
	class scrThread;

	class scriptIdBase
	{
	public:
		virtual ~scriptIdBase() = default; // 0 (0x00)

		// Assumes the script thread's identity.
		virtual void Reset(scrThread*) {}; // 1 (0x08)

		// Returns whether the hash of the script id is valid.
		virtual bool IsValid()
		{
			return false;
		}; // 2 (0x10)

		// Gets the hash of the script id.
		virtual std::uint32_t* GetHash(std::uint32_t* out)
		{
			return 0;
		}; // 3 (0x18)

		// Gets an unknown value from the script id.
		virtual std::uint32_t* GetUniqueId(std::uint32_t* out)
		{
			return 0;
		}; // 4 (0x20)

		// Gets the name of the script id. This function is not thread-safe and the resulting name must be copied out of the ptr immediately
		virtual const char* GetDebugName()
		{
			return nullptr;
		}; // 5 (0x28)

		// Serializes the script id from the buffer.
		virtual void Deserialize(datBitBuffer* buffer) {}; // 6 (0x30)

		// Serializes the script id to the buffer.
		virtual void Serialize(datBitBuffer* buffer) {}; // 7 (0x38)

		// Calculates some information with the position hash & instance id.
		virtual std::uint32_t GetSize()
		{
			return 0;
		}; // 8 (0x40)

		// Calls _0x40 and returns it's value added to another value.
		virtual std::uint32_t GetSizeWithHeader()
		{
			return 0;
		}; // 9 (0x48)

		// Logs some information about the script id.
		virtual void LogInfo(netLoggingInterface* logger) {}; // 10 (0x50)

		// Copies the information of other to this object.
		virtual void CopyData(scriptIdBase* other)
		{
		} // 11 (0x58)

		// Returns whether the other script id is equal.
		virtual bool operator==(scriptIdBase*)
		{
			return false;
		}; // 12 (0x60)

		// Populates the script name from the hash
		virtual void PopulateScriptName() {}; // 13 (0x68)

		// return this->IsValid() && this->m_Hash == other->m_Hash;
		virtual bool IsHandlerForSameScript(scriptIdBase* other)
		{
			return false;
		}; // 14 (0x70)
	};
}