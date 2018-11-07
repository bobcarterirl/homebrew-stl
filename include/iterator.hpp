#pragma once

namespace hbstl
{

template<typename Iter>
class reverse_iterator
{
public:
    using iterator_type = Iter;
    // TODO iterator_trats<Iter> members

    // Constructors
    reverse_iterator();
    reverse_iterator(Iter it);

    // Accessors
    Iter base() const;

    // TODO Arithmetic operators

    // Arithmetic assignment operators
    reverse_iterator& operator++ ();
    reverse_iterator operator++ (int);
    // TODO +=, -=, --

    // Dereference operators
    decltype(*Iter()) operator* () const;
    // TODO ->, []

private:
    Iter it;
};


// Relational operators

template<typename Iter>
bool operator== (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);

template<typename Iter>
bool operator!= (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);

// TODO <, <=, >, >=


// Template member function implementations

// Constructors

template<typename Iter>
reverse_iterator<Iter>::reverse_iterator() : it() {}

template<typename Iter>
reverse_iterator<Iter>::reverse_iterator(Iter it) : it(it) {}


// Accessors

template<typename Iter>
Iter reverse_iterator<Iter>::base() const { return it; }


// Arithmetic assignment operators

template<typename Iter>
reverse_iterator<Iter>& reverse_iterator<Iter>::operator++ () { --it; }

template<typename Iter>
reverse_iterator<Iter> reverse_iterator<Iter>::operator++ (int)
{
    auto temp = *this;
    --it;
    return temp;
}


// Dereference operators

template<typename Iter>
decltype(*Iter()) reverse_iterator<Iter>::operator* () const { return *(it-1); }


// Template non-member function implementations

// Relational operators

template<typename Iter>
bool operator== (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
    return lhs.base() == rhs.base();
}

template<typename Iter>
bool operator!= (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
    return !(lhs == rhs);
}

}
