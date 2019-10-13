////////////////////////////////////////////////////////////////////////////////
// Module Name:  int_stack.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "int_stack.h"
#include <iostream>


namespace xi {

// TODO: add method definitions here

    void IntStack::push(int el) {
        _head++;
        if (_head >= _ssize) throw std::logic_error("Out of bounds exception");
        _stack[_head] = el;
    }

    int IntStack::pop() {
        if (_head < 0) throw std::logic_error("Out of bounds exception");
        int value = _stack[_head];
        _head--;
        return value;
    }

    int IntStack::top() {
        if (_head < 0) throw std::logic_error("Out of bounds exception");
        return _stack[_head];
    }

    void IntStack::clear() {
        _head = 0;
    }

    bool IntStack::isEmpty() const {
        return _head == 0;
    }

    bool IntStack::isFull() const {
        return _head == _ssize - 1;
    }
} // namespace xi

