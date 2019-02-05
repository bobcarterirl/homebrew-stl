#include "algorithm.hpp"
#include "functional.hpp"
#include "iterator.hpp"
#include "limits.hpp"
#include "memory.hpp"
#include "utility.hpp"


namespace hsl
{

template<typename T, typename Alloc = allocator<T> >
class vector
{
public:
    using value_type = T;
    using allocator_type = Alloc;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using iterator = pointer;


    // Constructors
    vector() noexcept = default;

    vector(size_type count,
            const_reference value,
            const allocator_type& alloc = allocator_type()) :
        alloc(alloc) { assign(count, value); }

    vector(size_type count, const allocator_type& alloc = allocator_type()) :
        alloc(alloc) { resize(count); }

    // Assignment
    void assign(size_type count, const_reference value)
    {
        resize(count);
        fill(begin(), end(), value);
    }

    // Element access
    reference operator[] (size_type pos) { return arr[pos]; }


    // Iterators
    iterator begin() noexcept { return arr.get(); }
    iterator end() noexcept { return arr.get() + size(); }


    // Capacity
    bool empty() const noexcept { return size() == 0; }
    size_type size() const noexcept { return arr_size; }

    size_type max_size() const noexcept
    { return numeric_limits<size_type>::max; }

    void reserve(size_type new_cap)
    {
        if (new_cap > arr_cap)
        {
            // We reserve the exact amount of space requested because reserve
            // is mostly used when we know (at most) how much we'll need
            using namespace placeholders;
            function<void(pointer)> del = bind(&vector::delete_arr, this, _1);
            decltype(arr) new_arr(alloc.allocate(new_cap), del);

            swap_ranges(begin(), end(), new_arr.get());
            swap(arr, new_arr);

            arr_cap = new_cap;
        }
    }

    size_type capacity() const noexcept { return arr_cap; }
    
    // Modifiers
    void clear() { resize(0); }

    void resize(size_type count)
    {
        reserve(count);
        arr_size = count;
    }


private:
    allocator_type alloc;
    size_type arr_size = 0;
    size_type arr_cap = 0;
    unique_ptr<value_type[], function<void(pointer)> > arr;

    void delete_arr(pointer p) { alloc.deallocate(p, arr_cap); }
};

}
