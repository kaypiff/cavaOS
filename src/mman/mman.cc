
#include <memory.hh>

namespace cava::mman {
    
    node *memory_manager::find_best_fit(size_t size) const
    {
        node *current;
        int i;

        for (i = m_node_count; i >= 0; i--) {
            current = &m_node_buffer[MAX_ALLOC_NODES - i];
            if (!current->used && current->size >= size)
                return current;
        }
        
        return nullptr;
    }


    void memory_manager::sort_memory_by_size();

    memory_manager::memory_manager()
    : m_node_buffer {}
    , m_node_count { 0 }
    {
    }

    void *memory_manager::malloc(size_t size)
    {
        size_t a, b, i;
        bool smaller_used;
        node *best_fit;
        void *result;

        if (m_node_count >= MAX_ALLOC_NODES)
            return nullptr;

        best_fit = find_best_fit(size);

        if (!best_fit)
            return nullptr;
        
        if (best_fit->size - size < MAX_LEFTOVER_SPACE) {
            best_fit->used = 1;
            return best_fit->memory;
        }

        /* Block sizes after the split */
        a = size;
        b = best_fit->size - size;
        
        smaller_used = true;
        
        if (a > b) {
            a = b;
            b = size;
            smaller_used = false;
        }

        /* O(n) sorting of memory. A special case when splitting blocks. */

        i = MAX_ALLOC_NODES - m_node_count;

        /* Move all blocks smaller than A to the left */
        while (m_node_buffer[i].size < a && i < MAX_ALLOC_NODES) {
            m_node_buffer[i - 1] = m_node_buffer[i];
            i++;
        }

        if (i >= MAX_ALLOC_NODES)
            return nullptr;
        
        m_node_buffer[i] = {
            .memory = best_fit->memory,
            .size = a,
            .used = smaller_used,
        };

        result = best_fit->memory;

        best_fit->memory += a;
        best_fit->size = b;
        best_fit->used = !smaller_used;

        if (!smaller_used)
            result += a;
        
        node_count++;

        return result;
    }

    void memory_manager::free(void *ptr)
    {
        
    }
}
