// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef QUADTREE_IT_POSTORDER_H
#define	QUADTREE_IT_POSTORDER_H

#include <iterator>
#include <memory> // shared_ptr
#include <stack>
#include "quadtree.h"

namespace mzlib
{

    // Post-order iterator through all nodes
    template<class T>
    class quadtree_it_postorder : public std::iterator<std::forward_iterator_tag, T>
    {

    private:
        cquadnode<T>* m_current_node;
        std::stack<cquadnode<T>*> m_stack;

        void stack_nw_branch()
        {
            auto node = m_stack.top();
            while((node = node->m_child_nw.get()) != nullptr) {
                m_stack.push(node);
            }
        }
        
        void next_node()
        {
            if(!m_stack.empty()) {
                m_current_node = m_stack.top();
                m_stack.pop();
                auto node = m_current_node->get_next_sibling();
                if(node!=nullptr) {
                    m_stack.push(node);
                    stack_nw_branch();
                }
            }
            else {
                // to ensure that it can't be used twice in the end, and that
                // iteration that reached starting point equals to one that was
                // initialised as end() by the cquadtree
                m_current_node = nullptr;
            }
        }
        
    public:

        quadtree_it_postorder(cquadnode<T>* node) : 
            m_current_node(node)
        { 
            if(node!=nullptr) {
                m_stack.push(m_current_node);
                stack_nw_branch();
                next_node();
            }
        }

        quadtree_it_postorder(quadtree_it_postorder&&) = default; // make default move constructor

        quadtree_it_postorder(const quadtree_it_postorder&) = default; // make default copy constructor

        quadtree_it_postorder* operator++() 
        { 
            next_node();
            return this;
        }
        
        quadtree_it_postorder* operator++(int) 
        { 
            next_node();
            return this;
        }

        cquadnode<T>* operator->() const
        { 
            return m_current_node;
        }

        cquadnode<T>& operator*() const
        { 
            return *m_current_node; 
        }

        bool operator==(const quadtree_it_postorder& other) const 
        { 
            // Infinite recursion guard
            if(this == &other) return true;
            // After this, compare all fields
            return (this->m_stack.size() == other.m_stack.size() &&
                    this->m_current_node == other.m_current_node);  
        }

        bool operator!=(const quadtree_it_postorder& other) const 
        { 
            return !(*this == other); 
        }
    };

}

#endif	/* QUADTREE_IT_POSTORDER_H */

