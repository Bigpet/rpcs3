#include "stdafx.h"
#include "Emu/Memory/Memory.h"
#include "PPCDecoder.h"

u32 PPCDecoder::DecodeMemory(const u32 address)
{
	u32 instr = vm::read32(address);
	Decode(instr);

	if (instr == 0)
	{
		return 0;
	}
	return sizeof(u32);
}