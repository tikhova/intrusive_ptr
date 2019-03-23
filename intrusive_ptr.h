#ifndef INTRUSIVE_PTR_H
#define INTRUSIVE_PTR_H

#include <utility>
#include <iostream>

class interface {
public:
    virtual void add_ref() = 0;
    virtual void release() = 0;
    virtual int get_refcnt() = 0;
    virtual ~interface() {}
};

template <typename T>
class ptr_wrapper : public interface {
public:
    T* ptr = nullptr;
    ptr_wrapper(T* p) : ptr(p) { }
    ptr_wrapper(ptr_wrapper* p) : ptr(p->ptr) { }

    void add_ref() { if (ptr) ptr->add_ref(); }
    void release() { if (ptr) ptr->release(); }
    int get_refcnt() { if (ptr) ptr->get_refcnt(); }
    ~ptr_wrapper() = default;
};


template <class T>
class intrusive_ptr {
private:
    T* ptr;
    interface* wrapper;

public:
    // Constructors & destructor
    intrusive_ptr(T * p) noexcept : ptr(p), wrapper(new ptr_wrapper<T>(p)) {
        add_ref();
    }

    template <class Derived, typename = std::enable_if<std::is_base_of<T, Derived>::value>>
    intrusive_ptr(Derived * p) noexcept : ptr(p), wrapper(new ptr_wrapper(p)) {
        add_ref();
    }

    intrusive_ptr(const intrusive_ptr & p = nullptr) noexcept : ptr(p.ptr), wrapper(new ptr_wrapper(p))  {
        add_ref();
    }

    intrusive_ptr(intrusive_ptr && other) noexcept : ptr(other.ptr), wrapper(other.wrapper) {
        other.release();
    }

    template <class Derived, typename = std::enable_if<std::is_base_of<T, Derived>::value>>
    intrusive_ptr(intrusive_ptr<Derived> & other) noexcept : ptr(other.ptr), wrapper(new ptr_wrapper(other.wrapper)) {
        add_ref();
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
        swap(wrapper, other.wrapper);
    }

    // Access
    int get_count() const noexcept {
        get_refcnt();
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
    void add_ref() noexcept {
        wrapper->add_ref();
    }

    void release() noexcept {
        wrapper->release();
    }

    int get_refcnt() noexcept {
        return wrapper->get_refcnt();
    }
};

template <class Derived, class Base, typename = std::enable_if<std::is_base_of<Base, Derived>::value>>
intrusive_ptr<Derived> dynamic_pointer_cast(intrusive_ptr<Base> const & derived) noexcept {
    return intrusive_ptr<Derived>(dynamic_cast<Derived*>(derived.get()));
}

#endif // INTRUSIVE_PTR_H
