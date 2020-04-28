#pragma once
#include <tuple>
#include <iostream>

// Simple array class.
// The initialize(...) method directly forwards a variadic number of arguments to the constructor of E.
// Similarly, the constructor of Array forwards all arguments following the size to initialize.
template<typename E>
class Array {
    E *m_pStart;
    E *m_pStop;

public:
    template<typename ...Cs>
    Array(int size, Cs... args) {
        m_pStart = static_cast<E *>(malloc(size * sizeof(E)));
        m_pStop = m_pStart + size;
        initialize(args...);
    }

    virtual ~Array() {
        if (!std::is_trivially_destructible<E>::value)
            for (E *pDest = m_pStart; pDest < m_pStop; pDest++)
                pDest->~E();
        free(m_pStart);
    }

    int size() const {
        return m_pStop - m_pStart;
    }

    E *begin() const {
        return m_pStart;
    }

    E *end() const {
        return m_pStop;
    }

    const E &operator[](int i) const {
        return m_pStart[i];
    }

    E &operator[](int i) {
        return m_pStart[i];
    }

    template<typename ...Cs>
    void initialize(Cs... args) {
        for (E *pDest = m_pStart; pDest < m_pStop; pDest++)
            new(pDest) E(args...);
    }
};

template<typename E>
std::ostream &operator<<(std::ostream &os, const Array<E> &obj) {
    os << "Array<" << typeid(E).name() << ">(" << obj.size() << "): ";
    int c = 0;
    for (E &val : obj) {
        if (c > 0) os << ", ";
        os << c << ": " << val;
        ++c;
    }
    return os;
}

// ArrayWithDefault is a Array, which has the variadic arguments to the constructor stored in a tuple.
// initialize_with_default() allows to call initialize reusing the arguments passed as default to the constructor.
template<typename E, typename ...Cs>
class ArrayWithDefault : public Array<E> {
public:
    std::tuple<Cs...> m_default;

    ArrayWithDefault(int size, Cs... args) : Array<E>(size, args...), m_default(args...) {};

    void initialize_with_default() {
        // we need to put this in front of the tuple to call the member function
        std::apply(&Array<E>::template initialize<Cs...>, std::tuple_cat(std::make_tuple(this), m_default));
        // note that std::apply is C++17, but can easily be emulated using C++11 std::bind or std::call_once
        // see https://stackoverflow.com/q/32918679
    }
};

// Alias for an Array that will copy-construct a default value, similar to what NodeArray does.
template<typename E>
using ArrayWithCopiedDefault = ArrayWithDefault<E, E>;
