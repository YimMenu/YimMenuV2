#pragma once

#define DEFINE_RAGE_RTTI(className)      \
private:                                 \
	virtual void* _0x00() = 0;           \
	virtual void* _0x08() = 0;           \
	virtual uint32_t _0x10() = 0;        \
	virtual className* _0x18(void*) = 0; \
	virtual bool _0x20(void*) = 0;       \
	virtual bool _0x28(void**) = 0;      \
	virtual void destructor() = 0;       \
                                         \
public:
