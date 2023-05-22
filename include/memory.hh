
#pragma once

#include <types.hh>

#define MAX_NODE_COUNT 0x10000
#define NODE_BITMAP_SIZE (MAX_NODE_COUNT / 8)

namespace cava {

    class mman {

        class rbt {
            struct node {
                void *dataptr;
                uint32_t colour : 1;
                uint32_t size : 31;
                node *left, *right, *parent;
            };

            node *new_node(void *data, size_t size, bool used);
            void del_node(node *n);
            node *rotate_left(node *n);
            node *rotate_right(node *n);
            node *do_insert(node *root, void *data, size_t size, bool used);
            node *insert(void *data, size_t size, bool used);

            node *m_root;
            bool m_ll, m_rr, m_lr, m_rl;
            node m_node_buffer[MAX_NODE_COUNT];
            uint8_t m_node_bitmap[NODE_BITMAP_SIZE];
        public:
            rbt();
            ~rbt() = default;
        };

        rbt m_used;
        rbt m_unused;
    public:
        void *malloc(size_t size);
        void free(void *ptr);
        void *realloc(void *ptr, size_t size);
    };

    inline mman kernel_mman;

    static inline void *malloc(size_t size)
    {
        return kernel_mman.malloc(size);
    }

    static inline void free(void *ptr)
    {
        kernel_mman.free(ptr);
    }

    static inline void *realloc(void *ptr, size_t size)
    {
        return kernel_mman.realloc(ptr, size);
    }
}
