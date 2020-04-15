#ifndef functions_h
#define functions_h

namespace func {
template <class InputIterator, class UnaryPredicate>
bool any_of(InputIterator first, InputIterator last, UnaryPredicate predicate) {
    while (first != last) {
        if (predicate(*first)) {
            return true;
        }
        first++;
    }
    return false;
}

template <class ForwardIterator, class Compare>
ForwardIterator is_sorted_until(ForwardIterator first, ForwardIterator last, Compare compare) {
    if (first != last) {
        ForwardIterator i = first;
        while (++i != last) {
            if (compare(*i, *first)) {
                return i;
            }
            first = i;
        }
    }
    return last;
}

template <class ForwardIterator, class Compare>
bool is_sorted(ForwardIterator first, ForwardIterator last, Compare comp) {
    return func::is_sorted_until(first, last, comp) == last;
}

template <class BidirectionalIterator>
bool is_palindrome(BidirectionalIterator first, BidirectionalIterator last) {
    if (first == last) {
        return true;
    }

    last--;
    
    while (first != last) {
        if (*first != *last) {
            return false;
        }
        if (first == last || first == last + 1) {
            break;
        }
        first++;
        last--;
    }
    return true;
}
}

#endif
