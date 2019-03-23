#ifndef INTRUSIVE_PTR_H
#define INTRUSIVE_PTR_H

#include <utility>
#include <type_traits>
#include <iostream>

template <class T>
class intrusive_ptr {
private:
    T* ptr = nullptr;

public:
    // Constructors & destructor
    intrusive_ptr(T * p) noexcept : ptr(p) {
        add_ref();
    }

    intrusive_ptr(const intrusive_ptr & p = nullptr) noexcept : ptr(p)  {
        add_ref();
    }

    intrusive_ptr(intrusive_ptr && other) noexcept : ptr(other.ptr) {
        other.release();
    }

    ~intrusive_ptr() noexcept {
        release();
    }

    // Modification

    intrusive_ptr& operator=(const intrusive_ptr & other) noexcept {
        this->swap(intrusive_ptr(other));
        return *this;
    }

    intrusive_ptr& operator=(intrusive_ptr && other) noexcept {
        swap(intrusive_ptr(std::move(other)));
        return *this;
    }

    void swap(intrusive_ptr & other) noexcept {
        swap(ptr, other.ptr);
    }

    // Access
    int get_count() const noexcept {
        if (ptr) return ptr->get_refcnt();
        return 0;
    }

    T& operator*() const noexcept{
      return *ptr;
    }

    T* operator->() const noexcept{
      return ptr;
    }

    T* get() const noexcept {
        return ptr;
    }

    explicit operator bool() const noexcept{
      return ptr != nullptr;
    }

private:
    void add_ref() noexcept { if (ptr) ptr->add_ref(); }

    void release() noexcept {
        if (ptr) ptr->release();
    }
};

template <class U, class T, typename = std::enable_if<std::is_base_of<U, T>::value>>
intrusive_ptr<U> dynamic_pointer_cast(intrusive_ptr<T> const & derived) noexcept {
    return intrusive_ptr<U>(dynamic_cast<U*>(derived.get()));
}

#endif // INTRUSIVE_PTR_H
