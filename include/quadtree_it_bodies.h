// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef QUADTREE_IT_BODIES_H
#define	QUADTREE_IT_BODIES_H

#include <iterator>
#include <memory> // shared_ptr
#include "quadtree.h"

namespace mzlib
{
    // Const iterator through all bodies
    // Order of traversal: parent -> nw -> ne -> sw -> se -> parent
    template<class T>
    class quadtree_it_bodies : public std::iterator<std::forward_iterator_tag, T>
    {

    private:
        cquadnode<T>* m_start_node;
        cquadnode<T>* m_leaf;
        typename std::vector<T>::iterator m_body_it;

        cquadnode<T>* next_viable_leaf(
            const cquadnode<T>* const leaf) const 
        {
            const cquadnode<T>* node = leaf;
            while(node != nullptr) {
                if(node->is_nw_child()) {
                    return node->m_parent->m_child_ne->get_nw_leaf();
                }
                else if(node->is_ne_child()) {
                    return node->m_parent->m_child_sw->get_nw_leaf();
                }
                else if(node->is_sw_child()) {
                    return node->m_parent->m_child_se->get_nw_leaf();
                }
                else {   // last node, sw
                    if(node->m_parent.get() == m_start_node) return nullptr; // don't go around again
                    node = node->m_parent.get(); // try nieces and nephews next
                }
            }
            return nullptr;
        }

        // Returns pointer, because there is a possibility that there will be no leaves with children.
        // Could throw, but I don't see this as an exceptional behaviour.
        // Receives pointer, because the argument could be nullptr.
        // Could receive reference and use that, but then I would just make the caller of the function
        // do the null check, and it is better that low-level function is messy then high-level operations.
        cquadnode<T>* find_leaf_with_children(
            cquadnode<T>* leaf) const 
        {
            if(leaf == nullptr) return nullptr;
            cquadnode<T>* candidate = leaf;
            while(candidate->m_bodies.size()<=0) { // find children
                candidate = next_viable_leaf(candidate); // if no children on this leaf, try next
                if(candidate == nullptr) { // if no more leaves, give up
                    break;
                }
            }
            return candidate;
        }

        quadtree_it_bodies<T>* next_body() 
        {
            m_body_it = ++m_body_it;
            if(m_body_it == m_leaf->m_bodies.end()) {
                m_leaf = next_viable_leaf(m_leaf); // if no more children on this leaf, try next
                m_leaf = find_leaf_with_children(m_leaf);
                if(m_leaf != nullptr) {
                    m_body_it = m_leaf->m_bodies.begin();
                }
            }
            return this;
        }

        void setup(cquadnode<T>* init_node) 
        {
            m_leaf = init_node;
            if(init_node != nullptr) {
                cquadnode<T>* first_leaf = init_node->get_nw_leaf();
                m_leaf = find_leaf_with_children(first_leaf);
                if(m_leaf != nullptr) {
                    m_body_it = m_leaf->m_bodies.begin();
                }
            }
        }

    public:

        quadtree_it_bodies(
            cquadnode<T>* node) 
            : 
            m_start_node(node) 
        { 
            setup(m_start_node); 
        }
        quadtree_it_bodies(quadtree_it_bodies&&) = default; // make default move constructor
        quadtree_it_bodies(const quadtree_it_bodies&) = default; // make default copy constructor

        quadtree_it_bodies* operator++() 
        { 
            return next_body(); 
        }
        
        quadtree_it_bodies* operator++(int) 
        { 
            return next_body(); 
        }

        T& operator->() const
        { 
            return *m_body_it;
        }

        T& operator*() const
        { 
            return *m_body_it; 
        }

        bool operator==(const quadtree_it_bodies& other) const 
        { 
            // Infinite recursion guard
            if(this == &other) return true;
            // Leaf equal to nullptr means the end. Every iteration is equal in the end.
            if(this->m_leaf == other.m_leaf && this->m_leaf == nullptr) return true;
            // After this, compare all fields
            return (
                this->m_body_it == other.m_body_it &&
                this->m_leaf == other.m_leaf &&
                this->m_start_node == other.m_start_node);  
        }

        bool operator!=(const quadtree_it_bodies& other) const 
        { 
            return !(*this == other); 
        }
    };

}

#endif	/* QUADTREE_IT_BODIES_H */

