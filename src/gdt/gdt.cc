
#include <sys/gdt.hh>

extern "C" void load_gdt(uint16_t limit, uint8_t *base);

namespace cava::sys {
    void gdt::encode(uint32_t base, uint16_t limit, uint8_t access, uint8_t flags)
    {
        if (limit > 0xfffff)
            return; /* TODO: kernel error */
        
        if (m_num_entries >= MAX_GDT_ENTRIES)
            return; /* TODO: kernel error */
        
        uint8_t *target = &m_gdt[m_num_entries * GDT_ENTRY_SIZE];

        target[0] = limit & 0xff;
        target[1] = (limit >> 8) & 0xff;
        target[6] = (limit >> 16) & 0xf;

        target[2] = base & 0xff;
        target[3] = (base >> 8) & 0xff;
        target[4] = (base >> 16) & 0xff;
        target[7] = (base >> 24) & 0xff;

        target[5] = access;
        target[6] |= flags << 4;

        m_num_entries++;
    }

    void gdt::load()
    {
        load_gdt(m_num_entries * GDT_ENTRY_SIZE - 1, m_gdt);
    }

}
