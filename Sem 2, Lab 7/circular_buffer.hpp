#ifndef circular_buffer_hpp
#define circular_buffer_hpp
#include "exception.hpp"

template <class T>
class circular_buffer {
    class Iterator: public std::iterator<std::random_access_iterator_tag, T> {
        T * _pointer = nullptr;
        
    public:
        using value_type = typename std::iterator<std::random_access_iterator_tag, T>::value_type;
        
        Iterator() {}
        
        Iterator(T * pointer): _pointer(pointer) {}
        
        Iterator(const Iterator & iterator): _pointer(iterator._pointer) {}
        
        bool operator==(Iterator & iterator) {
            return _pointer == iterator._pointer;
        }
        
        bool operator==(T * pointer) {
            return _pointer == pointer;
        }
        
        bool operator!=(Iterator & iterator) {
            return _pointer != iterator._pointer;
        }
        
        bool operator!=(T * pointer) {
            return _pointer != pointer;
        }
        
        bool operator<(Iterator & iterator) {
            return _pointer < iterator._pointer;
        }
        
        bool operator<(T * pointer) {
            return _pointer < pointer;
        }
        
        bool operator>(Iterator & iterator) {
            return _pointer > iterator._pointer;
        }
        
        bool operator>(T * pointer) {
            return _pointer > pointer;
        }
        
        bool operator<=(Iterator & iterator) {
            return _pointer <= iterator._pointer;
        }
        
        bool operator<=(T * pointer) {
            return _pointer <= pointer;
        }
        
        bool operator>=(Iterator & iterator) {
            return _pointer >= iterator._pointer;
        }
        
        bool operator>=(T * pointer) {
            return _pointer >= pointer;
        }
        
        T & operator*() {
            return * _pointer;
        }
        
        T * operator->() {
            return _pointer;
        }
        
        Iterator & operator++() {
            _pointer++;
            return * this;
        }
        
        Iterator operator++(T) {
            Iterator iterator(* this);
            ++_pointer;
            return iterator;
        }
        
        Iterator & operator--() {
            _pointer--;
            return * this;
        }
        
        Iterator operator--(T) {
            Iterator iterator(* this);
            --_pointer;
            return iterator;
        }
        
        Iterator & operator+=(Iterator & iterator) {
            _pointer += iterator._pointer;
            return * this;
        }
        
        Iterator & operator+=(value_type shift) {
            _pointer += shift;
            return * this;
        }
        
        Iterator & operator-=(Iterator & iterator) {
            _pointer -= iterator._pointer;
            return * this;
        }
        
        Iterator operator+(value_type shift) {
            return Iterator(_pointer + shift);
        }
        
        Iterator operator-(value_type shift) {
            return Iterator(_pointer - shift);
        }
        
        Iterator & operator=(Iterator & iterator) {
            if (_pointer != iterator._pointer) {
                _pointer = iterator._pointer;
            }
            
            return * this;
        }
        
        Iterator & operator=(T * pointer) {
            if (_pointer != pointer) {
                _pointer = pointer;
            }
            
            return * this;
        }
        
        value_type operator-(Iterator & iterator) {
            return static_cast<int>(_pointer - iterator._pointer);
        }
        
        value_type operator+(Iterator & iterator) {
            return _pointer - iterator._pointer;
        }
    };
    
    T & operator[](int index) {
        return _data[index % _capacity];
    }
    
    T * _data = nullptr;
    
    int _capacity = 0;
    int _size = 0;
    
    Iterator _begin;
    Iterator _end;
    
    int _push_front_index = 0;
    int _push_back_index = 0;
    
    void init(int begin_index, int end_index) {
        _data = new T[_capacity];
        
        if (begin_index > -1) {
            _begin = & _data[begin_index];
        }
        
        _end = & _data[end_index];
    }
    
    void de_init() {
        _begin = nullptr;
        _end = nullptr;
        
        delete [] _data;
    }
    
public:
    circular_buffer() {}
    
    circular_buffer(int capacity): _capacity(capacity) {
        if (_capacity == 0) {
            circular_buffer();
        } else if (_capacity > 0) {
            init(-1, 0);
        } else {
            throw Exception("Неверное значение капасити!");
        }
    }
    
    circular_buffer(int capacity, T object): _capacity(capacity), _size(capacity) {
        if (_capacity == 0) {
            circular_buffer();
        } else if (_capacity > 0) {
            init(0, _capacity);
            
            for (int i = 0; i < _capacity; i++) {
                _data[i] = object;
            }
            
            _push_front_index = _capacity - 1;
            
        } else {
            throw Exception("Неверное значение капасити!");
        }
    }
    
    ~circular_buffer() {
        de_init();
    }
    
    Iterator begin() { return _begin; }
    
    Iterator end() { return _end; }
    
    const Iterator begin() const { return _begin; }
    
    const Iterator end() const { return _end; }
    
    void push_back(T object) {
        if (_capacity > 0) {
            if (_size < _capacity) {
                if (_begin == nullptr) {
                    * _end = object;
                    _begin = _end;
                    
                    _end++;
                    _size++;
                } else {
                    * _end = object;
                    
                    _end++;
                    _size++;
                    
                    if (_size == _capacity) {
                        _push_front_index = _capacity - 1;
                    }
                }
            } else {
                _data[_push_back_index] = object;
                
                _push_back_index = (_push_back_index + 1) % _capacity;
            }
        } else {
            throw Exception("Капасити равно нулю!");
        }
    }
    
    void push_front(T object) {
        if (_capacity > 0) {
            if (_size < _capacity) {
                if (_begin == nullptr) {
                    * _end = object;
                    _begin = _end;
                    
                    _end++;
                    _size++;
                } else {
                    for (Iterator it = _end - 1; it >= _begin; it--) {
                        * (it + 1) = *it;
                    }
                    
                    * _begin = object;
                    
                    _end++;
                    _size++;
                    
                    if (_size == _capacity) {
                        _push_front_index = _capacity - 1;
                    }
                }
            } else {
                _data[_push_front_index] = object;
                
                _push_front_index = (_push_front_index + _capacity - 1) % _capacity;
            }
        } else {
            throw Exception("Капасити равно нулю!");
        }
    }
    
    void pop_back() {
        if (_size > 0) {
            _end--;
            _size--;
            
            if (_size == 0) {
                _begin = nullptr;
            }
        } else {
            std::cerr << "Буфер пуст!" << std::endl;
        }
    }
    
    void pop_front() {
        if (_size > 0) {
            for (Iterator it = _begin + 1; it < _end; it++) {
                * (it - 1) = * it;
            }
            _end--;
            _size--;
            
            if (_size == 0) {
                _begin = nullptr;
            }
        } else {
            std::cerr << "Буфер пуст!" << std::endl;
        }
    }
    
    void insert(Iterator position, T object) {
        if (position >= _begin && position < & _data[_capacity]) {
            if (_size < _capacity) {
                if (position == _begin) {
                    push_front(object);
                } else if (position == _end) {
                    push_back(object);
                } else {
                    for (Iterator it = & _data[_size - 1]; it >= position; it--) {
                        * (it + 1) = * it;
                    }
                    
                    *position = object;
                    
                    _end++;
                    _size++;
                }
            } else {
                * position = object;
            }
        } else {
            std::cerr << "Неверная позиция!" << std::endl;
        }
    }
    
    void erase(Iterator position) {
        if (position >= _begin && position < & _data[_capacity]) {
            if (_size > 0) {
                if (position == _begin) {
                    pop_front();
                } else if (position == & _data[_size - 1]) {
                    pop_back();
                } else {
                    for (Iterator it = position; it < & _data[_size - 1]; it++) {
                        * it = * (it + 1);
                    }
                    
                    _end--;
                    _size--;
                }
            } else {
                std::cerr << "Буфер пуст!" << std::endl;
            }
        } else {
            std::cerr << "Неверная позиция!" << std::endl;
        }
    }
    
    void resize(int capacity) {
        if (capacity == 0) {
            de_init();
            
            _push_back_index = 0;
            _push_front_index = 0;
        } else if (capacity > 0 && _capacity == 0) {
            _capacity = std::move(capacity);
            
            init(-1, 0);
            
            _push_front_index = _capacity - 1;
        } else if (capacity >= _size) {
            _capacity = std::move(capacity);
            T * temp_buffer = new T[_capacity];
            
            for (int i = 0; i < _size; i++) {
                temp_buffer[i] = _data[i];
            }
            
            de_init();
            
            init(0, _size);
            
            for (int i = 0; i < _size; i++) {
                _data[i] = temp_buffer[i];
            }
            
            delete [] temp_buffer;
        } else if (capacity > 0 && capacity < _size) {
            _capacity = std::move(capacity);
            _size = _capacity;
            T * temp_buffer = new T[_capacity];
            
            for (int i = 0; i < _capacity; i++) {
                temp_buffer[i] = _data[i];
            }
            
            de_init();
            
            init(0, _capacity);
            
            for (int i = 0; i < _capacity; i++) {
                _data[i] = temp_buffer[i];
            }
            
            delete [] temp_buffer;
            
            _push_front_index = _capacity - 1;
        } else if (capacity < 0) {
            std::cerr << "Неверное значение капасити!" << std::endl;
        }
    }
    
    void resize(int capacity, T object) {
        if (capacity == 0) {
            resize(0);
        } else if (capacity > 0) {
            _capacity = std::move(capacity);
            _size = _capacity;
            
            init(0, _capacity);
            
            _push_front_index = _capacity - 1;
            
            for (int i = 0; i < _capacity; i++) {
                _data[i] = object;
            }
        } else {
            std::cerr << "Неверное значение капасити!" << std::endl;
        }
    }
    
    void shrink_to_fit() {
        resize(_size);
    }
    
    int size() { return _size; }
    
    void clear() {
        de_init();
        
        _push_front_index = 0;
        _push_back_index = 0;
    }
    
    void print() {
        std::cout << "Капасити: " << _capacity << std::endl;
        std::cout << "Заполнено: " << _size << std::endl;
        
        if (_size == 0) {
            std::cout << "Буфер пуст!" << std::endl;
        } else {
            for (int i = 0; i < _size; i++) {
                std::cout << "[" << _data[i] << "] ";
            }
            std::cout << std::endl;
        }
    }
};

#endif
