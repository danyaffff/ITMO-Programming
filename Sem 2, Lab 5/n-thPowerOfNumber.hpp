#ifndef n_thPowerOfNumber_hpp
#define n_thPowerOfNumber_hpp

template <typename T>
T pow(T base, int power) {
    T temp = base;
    for (int i = 0; i < power - 1; i++) {
        temp *= base;
    }
    return temp;
}

#endif
