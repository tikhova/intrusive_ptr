#include <iostream>
#include <memory>#include <iostream>
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
    std::string type = "A";
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
};

struct B : A {
    std::string type = "B";
    int val = 5;
    B(int v) : val(v) {}
    const int & get_val() const { return val; }
};

struct C {
    void add_ref() { }
    void release() { }
    int get_refcnt() { return 0; }
};


int main() {
    A a;
    B b(3);
    C c;
    auto a_ptr = intrusive_ptr<A>(&a);
    auto b_ptr = intrusive_ptr<B>(&b);
    auto c_ptr = intrusive_ptr<C>(&c);
    auto cast = dynamic_pointer_cast<A>(b_ptr);
    // auto wrong_cast = dynamic_pointer_cast<A>(c_ptr);
    return 0;
}
