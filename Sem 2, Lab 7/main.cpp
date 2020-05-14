/* Лабораторная работа №7. Кольцевой буфер.
Реализовать кольцевой буфер в виде stl-совместимого контейнера (например, может быть использован с стандартными алгоритмами), 
обеспеченного итератором произвольного доступа. Реализация не должна использовать ни одни из контейнеров STL. */

#include <iostream>
#include "circular_buffer.hpp"

int main() {
    const int size = 10;
    
    try {
        circular_buffer<int> cb(size);
        
        cb.push_front(2);
        cb.push_front(3);
        cb.push_back(-1);
        cb.push_front(9);
        cb.push_front(0);
        cb.push_front(-9);
        
        std::cout << "Неотсортированный буфер: " << std::endl;
        cb.print();
        std::cout << std::endl;
        
        std::sort(cb.begin(), cb.end());
        
        std::cout << "Отсортированный буфер: " << std::endl;
        cb.print();
        std::cout << std::endl;
        
        cb.shrink_to_fit();
        
        cb.print();
    } catch (std::bad_alloc) {
        std::cerr << "Не удалось выделить память под буфер!" << std::endl;
        return 1;
    } catch (Exception & exception) {
        std::cerr << exception.what() << std::endl;
        return 1;
    }
}
