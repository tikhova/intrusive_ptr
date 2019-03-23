#include <iostream>
#include <memory>
#include <iostream>
#include <memory>
#include <algorithm>
#include <set>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <set>
#include <string>
#include <vector>
#include <functional>

#include "intrusive_ptr.h"

struct A {
    int ref_count = 0;
    void add_ref() {
        ++ref_count;
    }
    void release() {
        --ref_count;
        if (ref_count == 0) {
            // do stuff
        }
    }
    int get_refcnt() { return ref_count; }
    virtual ~A() { std::cout << "destr A" << std::endl; }
};

struct B : A {
    int b_ref_count = 0;
    int val = 5;
    B(int v) : val(v) {}
    const int & get_val() const { return val; }
    void add_ref() {
        ++b_ref_count;
    }
    void release() {
        --b_ref_count;
        if (b_ref_count == 0) {
            // do stuff
        }
    }
    int get_refcnt() {
        return b_ref_count;
    }
    ~B() { std::cout << "destr B" << std::endl; }
};

struct C {
    void add_ref() { }
    void release() { }
    int get_refcnt() { return 0; }
    ~C() { std::cout << "destr C" << std::endl; }
};


int main() {
    A a;
    B b(3);
    C c;
    auto a_ptr = intrusive_ptr<A>(&a);
    auto b_as_A_ptr = intrusive_ptr<A>(&b); // 1
    auto b_ptr = intrusive_ptr<B>(&b);      // 2
    auto a_derived = intrusive_ptr<A>(&b);  // 3
    auto c_ptr = intrusive_ptr<C>(&c);
    auto cast = dynamic_pointer_cast<B>(b_as_A_ptr); // 4
    std::cout << cast->get_refcnt() << std::endl;

    B new_b(5);
    intrusive_ptr<A> Bb(&new_b);
    intrusive_ptr<A> Bb2 = Bb;
    intrusive_ptr<B> Bd = dynamic_pointer_cast<B>(Bb);
    auto Bd2 = Bd;
    std::cout << Bd->get_refcnt() << std::endl;
    // auto wrong_cast = dynamic_pointer_cast<A>(c_ptr);
    return 0;
}
