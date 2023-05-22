
#include <memory.hh>

#define RED 0
#define BLACK 1

namespace cava {
        mman::rbt::node *mman::rbt::new_node(void *data, size_t size, bool used)
        {
            uint8_t bitmap_entry;

            for (size_t i = 0; i < NODE_BITMAP_SIZE; i++) {
                bitmap_entry = m_node_bitmap[i];

                if (bitmap_entry == 0xff)
                    continue;
                
                for (uint8_t bitmask = 0x80, j = 0; bitmask != 0; bitmask >>= 1, j++) {
                    if (bitmap_entry & bitmask)
                        continue;
                    
                    m_node_bitmap[i] |= bitmask;
                    
                    auto& created_node = m_node_buffer[i * 8 + j];
                    created_node.dataptr = data;
                    created_node.size = size;
                    return &created_node;
                }
            }

            return nullptr;
        }

        void mman::rbt::del_node(mman::rbt::node *n)
        {
            auto offset = (size_t)(n - m_node_buffer);
            auto i = offset >> 3;
            auto j = offset & 7;
            m_node_bitmap[i] &= ~(0x80 >> j);
        }

        mman::rbt::node *mman::rbt::rotate_left(mman::rbt::node *n)
        {
            node *x, *y;

            x = n->right;
            y = x->left;

            x->left = n;
            n->right = y;
            n->parent = x;

            if (y)
                y->parent = n;
            
            return x;
        }

        mman::rbt::node *mman::rbt::rotate_right(mman::rbt::node *n)
        {
            node *x, *y;

            x = n->left;
            y = x->right;

            x->right = n;
            n->left = y;
            n->parent = x;

            if (y)
                y->parent = n;
            
            return x;
        }

        mman::rbt::node *mman::rbt::do_insert(mman::rbt::node *root, void *data, size_t size, bool used)
        {
            bool red_red_conflict = false;

            if (!root)
                return new_node(data, size, used);
            
            if (size < root->size) {
                root->left = do_insert(root->left, data, size, used);
                root->left->parent = root;

                if (root != m_root) {
                    if (root->colour == RED && root->left->colour == RED)
                        red_red_conflict = true;
                }
            } else {
                root->right = do_insert(root->right, data, size, used);
                root->right->parent = root;

                if (root != m_root) {
                    if (root->colour == RED && root->right->colour == RED)
                        red_red_conflict = true;
                }
            }

            if (m_ll) {
                root = rotate_left(root);
                root->colour = BLACK;
                root->left->colour = RED;
                m_ll = false;
            } else if (m_rr) {
                root = rotate_right(root);
                root->colour = BLACK;
                root->left->colour = RED;
                m_rr = false;
            } else if (m_rl) {
                root->right = rotate_right(root->right);
                root->right->parent = root;
                root = rotate_left(root);
                root->colour = BLACK;
                root->left->colour = RED;
                m_rl = false;
            } else if (m_lr) {
                root->left = rotate_left(root->left);
                root->left->parent = root;
                root = rotate_right(root);
                root->colour = BLACK;
                root->right->colour = RED;
                m_lr = false;
            }

            if (!red_red_conflict)
                return root;
            
            if (root->parent->right == root) {
                if (!root->parent->left || root->parent->left->colour == BLACK) {
                    if (root->left && root->left->colour == RED)
                        m_rl = true;
                    else if (root->right && root->right->colour == RED)
                        m_lr = true;
                } else {
                    root->parent->left->colour = BLACK;
                    root->colour = BLACK;
                    if (root->parent != m_root)
                        root->parent->colour = RED;
                }
            } else {        
                if (!root->parent->right || root->parent->right->colour == BLACK) {
                    if (root->left && root->left->colour == RED)
                        m_rr = true;
                    else if (root->right && root->right->colour == RED)
                        m_lr = true;
                } else {
                    root->parent->right->colour = BLACK;
                    root->colour = BLACK;
                    if (root->parent != m_root)
                        root->parent->colour = RED;
                }
            }

            return root;
        }

        mman::rbt::node *mman::rbt::insert(void *data, size_t size, bool used)
        {
            if (m_root) {
                m_root = do_insert(m_root, data, size, used);
            } else {
                m_root = new_node(data, size, used);
                m_root->colour = BLACK;
            }

            return m_root;
        }
        
        mman::rbt::rbt()
        : m_root { NULL }
        , m_ll { false }
        , m_rr { false }
        , m_lr { false }
        , m_rl { false }
        , m_node_buffer {}
        , m_node_bitmap {}
        {
            for (size_t i = 0; i < NODE_BITMAP_SIZE; i++)
                m_node_bitmap[i] = 0;
        }
}
