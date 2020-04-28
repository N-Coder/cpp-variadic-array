#pragma once

#include <iostream>

// ExampleClass<is_copy_constructible, is_default_constructible> lets you decide whether it is
// copy / default constructible depending on the template values you pass
template<bool C, bool D>
class ExampleClass;

template<bool C, bool D>
std::ostream &operator<<(std::ostream &os, const ExampleClass<C, D> &obj);

template<>
class ExampleClass<false, false> {
public:
    int m_val;

    ExampleClass() = delete;

    ExampleClass(const ExampleClass &copy) = delete;

    ExampleClass(int val) : m_val(val) {
        std::cout << "ExampleClass<false, false>(int val) called with val=" << val << ": " << *this << std::endl;
    };
};

template<>
class ExampleClass<false, true> {
public:
    int m_val;

    ExampleClass() : m_val(0) {
        std::cout << "ExampleClass<false, true>() called: " << *this << std::endl;
    };

    ExampleClass(const ExampleClass &copy) = delete;

    ExampleClass(int val) : m_val(val) {
        std::cout << "ExampleClass<false, true>(int val) called with val=" << val << ": " << *this << std::endl;
    };
};

template<>
class ExampleClass<true, false> {
public:
    int m_val;

    ExampleClass() = delete;

    ExampleClass(const ExampleClass &copy) : m_val(copy.m_val) {
        std::cout << "ExampleClass<true, false>(const ExampleClass &copy) called with copy=" << copy << ": " << *this
                  << std::endl;
    };

    ExampleClass(int val) : m_val(val) {
        std::cout << "ExampleClass<true, false>(int val) called with val=" << val << ": " << *this << std::endl;
    };
};

template<>
class ExampleClass<true, true> {
public:
    int m_val;

    ExampleClass() : m_val(0) {
        std::cout << "ExampleClass<true, true>() called: " << *this << std::endl;
    };

    ExampleClass(const ExampleClass &copy) : m_val(copy.m_val) {
        std::cout << "ExampleClass<true, true>(const ExampleClass &copy) called with copy=" << copy << ": " << *this
                  << std::endl;
    };

    ExampleClass(int val) : m_val(val) {
        std::cout << "ExampleClass<true, true>(int val) called with val=" << val << ": " << *this << std::endl;
    };
};

template<bool C, bool D>
std::ostream &operator<<(std::ostream &os, const ExampleClass<C, D> &obj) {
    std::cout << "Instance ExampleClass<" << (C ? "true" : "false") << ", " << (D ? "true" : "false") << "> with val="
              << obj.m_val;
    return os;
}
