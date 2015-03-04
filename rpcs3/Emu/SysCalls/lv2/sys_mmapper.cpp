#include "stdafx.h"
#include "Emu/Memory/Memory.h"
#include "Emu/SysCalls/SysCalls.h"

#include "sys_memory.h"
#include "sys_mmapper.h"
#include <map>
#include <array>
#include <utility>

SysCallBase sys_mmapper("sys_mmapper");
std::map<u32, u32> mmapper_info_map;

//TODO: don't use this hardcoded but integrate it into Memory.cpp somehow
std::array<std::pair<u32, u32>, 8> mappable_mem = 
{{
	{ 0x30000000, 0 },
	{ 0x40000000, 0 },
	{ 0x50000000, 0 },
	{ 0x60000000, 0 },
	{ 0x70000000, 0 },
	{ 0x80000000, 0 },
	{ 0x90000000, 0 },
	{ 0xA0000000, 0 }
}};

u32 find_free_address(u32 size, u64 flags)
{
	//this is wrong and unsafe
	flags = flags & SYS_MEMORY_ACCESS_RIGHT_ANY;
	u32 addr = 0;
	for (int i = 0; i < mappable_mem.size(); ++i)
	{
		if (mappable_mem[i].second == 0 && size > 0)
		{
			size -= 0x10000000;
			mappable_mem[i].second = flags;
			if (!addr) addr = mappable_mem[i].first;
		}
	}
	return addr;
}

s32 sys_mmapper_allocate_address(u32 size, u64 flags, u32 alignment, u32 alloc_addr)
{
	sys_mmapper.Warning("sys_mmapper_allocate_address(size=0x%x, flags=0x%llx, alignment=0x%x, alloc_addr=0x%x)", 
		size, flags, alignment, alloc_addr);

	// Check for valid alignment.
	if(alignment > 0x80000000)
		return CELL_EALIGN;

	// Check requested size, should be a multiple of 265 MB
	if ((size % 0x10000000) || size == 0)
	{
		return CELL_EALIGN;
	}

	// Check page size.
	u32 addr;
	switch(flags & (SYS_MEMORY_PAGE_SIZE_1M | SYS_MEMORY_PAGE_SIZE_64K))
	{
	default:
	case SYS_MEMORY_PAGE_SIZE_1M:
		if(align(size, alignment) & 0xfffff)
			return CELL_EALIGN;
		//addr = (u32)Memory.Allocm(size, 0x100000);
	break;

	case SYS_MEMORY_PAGE_SIZE_64K:
		if (align(size, alignment) & 0xffff)
			return CELL_EALIGN;
		//addr = (u32)Memory.Allocm(size, 0x10000);
	break;
	}

	addr = find_free_address(size,flags);

	//if (!addr) return CELL_ENOMEM;
	// Write back the start address of the allocated area.
	vm::write32(alloc_addr, addr);

	return CELL_OK;
}

s32 sys_mmapper_allocate_fixed_address()
{
	sys_mmapper.Warning("sys_mmapper_allocate_fixed_address");

	// Allocate a fixed size from user memory.
	if (!Memory.Alloc(SYS_MMAPPER_FIXED_SIZE, 0x100000))
		return CELL_EEXIST;
	
	return CELL_OK;
}

s32 sys_mmapper_allocate_memory(u32 size, u64 flags, vm::ptr<u32> mem_id)
{
	sys_mmapper.Warning("sys_mmapper_allocate_memory(size=0x%x, flags=0x%llx, mem_id_addr=0x%x)", size, flags, mem_id.addr());

	// Check page granularity.
	switch(flags & (SYS_MEMORY_PAGE_SIZE_1M | SYS_MEMORY_PAGE_SIZE_64K))
	{
	case SYS_MEMORY_PAGE_SIZE_1M:
		if(size & 0xfffff)
			return CELL_EALIGN;
	break;

	case SYS_MEMORY_PAGE_SIZE_64K:
		if(size & 0xffff)
			return CELL_EALIGN;
	break;

	default:
		return CELL_EINVAL;
	}

	// Generate a new mem ID.
	std::shared_ptr<mmapper_info> info(new mmapper_info(size, flags));
	*mem_id = sys_mmapper.GetNewId(info);

	return CELL_OK;
}

s32 sys_mmapper_allocate_memory_from_container(u32 size, u32 cid, u64 flags, vm::ptr<u32> mem_id)
{
	sys_mmapper.Warning("sys_mmapper_allocate_memory_from_container(size=0x%x, cid=%d, flags=0x%llx, mem_id_addr=0x%x)", 
		size, cid, flags, mem_id.addr());

	// Check if this container ID is valid.
	std::shared_ptr<MemoryContainerInfo> ct;
	if(!sys_mmapper.CheckId(cid, ct))
		return CELL_ESRCH;

	// Check page granularity.
	switch(flags & (SYS_MEMORY_PAGE_SIZE_1M | SYS_MEMORY_PAGE_SIZE_64K))
	{
	case SYS_MEMORY_PAGE_SIZE_1M:
		if(size & 0xfffff)
			return CELL_EALIGN;
	break;

	case SYS_MEMORY_PAGE_SIZE_64K:
		if(size & 0xffff)
			return CELL_EALIGN;
	break;

	default:
		return CELL_EINVAL;
	}

	ct->size = size;

	// Generate a new mem ID.
	std::shared_ptr<mmapper_info> info(new mmapper_info(ct->size, flags));
	*mem_id = sys_mmapper.GetNewId(info, TYPE_MEM);

	return CELL_OK;
}

s32 sys_mmapper_change_address_access_right(u32 start_addr, u64 flags)
{
	sys_mmapper.Warning("sys_mmapper_change_address_access_right(start_addr=0x%x, flags=0x%llx)", start_addr, flags);

	// TODO

	return CELL_OK;
}

s32 sys_mmapper_free_address(u32 start_addr)
{
	sys_mmapper.Warning("sys_mmapper_free_address(start_addr=0x%x)", start_addr);

	// Free the address.
	Memory.Free(start_addr);
	return CELL_OK;
}

s32 sys_mmapper_free_memory(u32 mem_id)
{
	sys_mmapper.Warning("sys_mmapper_free_memory(mem_id=0x%x)", mem_id);

	// Check if this mem ID is valid.
	std::shared_ptr<mmapper_info> info;
	if(!sys_mmapper.CheckId(mem_id, info))
		return CELL_ESRCH;

	// Release the allocated memory and remove the ID.
	sys_mmapper.RemoveId(mem_id);

	return CELL_OK;
}

s32 sys_mmapper_map_memory(u32 start_addr, u32 mem_id, u64 flags)
{
	sys_mmapper.Warning("sys_mmapper_map_memory(start_addr=0x%x, mem_id=0x%x, flags=0x%llx)", start_addr, mem_id, flags);

	// Check if this mem ID is valid.
	std::shared_ptr<mmapper_info> info;
	if(!sys_mmapper.CheckId(mem_id, info))
		return CELL_ESRCH;

	// Map the memory into the process address.
	if (!Memory.Map(start_addr, info->size))
	{
		sys_mmapper.Error("sys_mmapper_map_memory failed!");
	//	return CELL_EBUSY;
	}
	// Keep track of mapped addresses.
	mmapper_info_map[start_addr] = mem_id;

	return CELL_OK;
}

s32 sys_mmapper_search_and_map(u32 start_addr, u32 mem_id, u64 flags, u32 alloc_addr)
{
	sys_mmapper.Warning("sys_mmapper_search_and_map(start_addr=0x%x, mem_id=0x%x, flags=0x%llx, alloc_addr=0x%x)",
		start_addr, mem_id, flags, alloc_addr);

	// Check if this mem ID is valid.
	std::shared_ptr<mmapper_info> info;
	if(!sys_mmapper.CheckId(mem_id, info))
		return CELL_ESRCH;
	
	// Search for a mappable address.
	u32 addr;
	bool found;
	for (int i = 0; i < SYS_MMAPPER_FIXED_SIZE; i += 0x100000)
	{
		addr = start_addr + i;
		found = Memory.Map(addr, info->size);
		if(found)
		{
			sys_mmapper.Warning("Found and mapped address 0x%x", addr);
			break;
		}
	}

	if (!found)
		return CELL_ENOMEM;
	
	// Write back the start address of the allocated area.
	vm::write32(alloc_addr, addr);

	// Keep track of mapped addresses.
	mmapper_info_map[addr] = mem_id;

	return CELL_OK;
}

s32 sys_mmapper_unmap_memory(u32 start_addr, u32 mem_id_addr)
{
	sys_mmapper.Warning("sys_mmapper_unmap_memory(start_addr=0x%x, mem_id_addr=0x%x)", start_addr, mem_id_addr);

	// Write back the mem ID of the unmapped area.
	u32 mem_id = mmapper_info_map.find(start_addr)->second;
	vm::write32(mem_id_addr, mem_id);

	return CELL_OK;
}

s32 sys_mmapper_enable_page_fault_notification(u32 start_addr, u32 q_id)
{
	sys_mmapper.Warning("sys_mmapper_enable_page_fault_notification(start_addr=0x%x, q_id=0x%x)", start_addr, q_id);

	// TODO

	return CELL_OK;
}
