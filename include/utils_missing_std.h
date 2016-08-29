//
// Not all code here is entirely written by me.
// Details beside every piece of code
//
// Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef UTILS_MISSING_STD_H
#define	UTILS_MISSING_STD_H

#include <memory>

// in anticipation of adoption of the newer c++ standard
namespace std {

// Herb Sutter's implementiation suggestion   
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

// Pretty much copied from: https://github.com/martinmoene/observer-ptr
template< class W >
class observer_ptr
{
public:
    typedef W   element_type;
    typedef W * pointer;
    typedef W & reference;

    constexpr observer_ptr() noexcept
    : ptr( nullptr ) {}

    constexpr observer_ptr( std::nullptr_t ) noexcept
    : ptr( nullptr ) {}

    constexpr explicit observer_ptr( pointer p ) noexcept
    : ptr(p) {}

    template< class W2 >
    constexpr observer_ptr(observer_ptr<W2> other ) noexcept
    : ptr( other.get() ) {}

    constexpr pointer get() const noexcept
    {
        return ptr;
    }

    constexpr reference operator*() const
    {
        return *ptr;
    }

    constexpr pointer operator->() const noexcept
    {
        return ptr;
    }

    constexpr explicit operator bool() const noexcept
    {
        return ptr != nullptr;
    }

    constexpr operator pointer() const noexcept
    {
        return ptr;
    }

    typedef void (observer_ptr::*safe_bool)() const;
    void this_type_does_not_support_comparisons() const {}

    constexpr operator safe_bool() const noexcept
    {
        return ptr != nullptr ? &observer_ptr::this_type_does_not_support_comparisons : 0;
    }

    constexpr pointer release() noexcept
    {
        pointer p( ptr );
        reset();
        return p;
    }

    constexpr void reset( pointer p = nullptr ) noexcept
    {
        ptr = p;
    }

private:
    pointer ptr;
};


} // namespace std

#endif	/* UTILS_MISSING_STD_H */

