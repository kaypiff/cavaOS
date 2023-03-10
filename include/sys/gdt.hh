
#pragma once

#include <types.hh>

#define MAX_GDT_ENTRIES 8
#define GDT_ENTRY_SIZE  8

namespace cava::sys {
    class gdt {
        uint8_t m_gdt[GDT_ENTRY_SIZE * MAX_GDT_ENTRIES];
        uint8_t m_num_entries;
    public:
        void encode(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
        void load();
    };
}
