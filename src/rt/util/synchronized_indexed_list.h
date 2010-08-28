#ifndef SYNCHRONIZED_INDEXED_LIST_H
#define SYNCHRONIZED_INDEXED_LIST_H

#include "indexed_list.h"

template<typename T> class synchronized_indexed_list :
    public indexed_list<T> {
    spin_lock _lock;
public:
    synchronized_indexed_list(memory_region &region) :
        indexed_list<T>(region) {
        // Nop.
    }

    int32_t append(T *value) {
        int32_t index = 0;
        _lock.lock();
        index = indexed_list<T>::append(value);
        _lock.unlock();
        return index;
    }

    size_t length() {
       size_t length = 0;
       _lock.lock();
       length = indexed_list<T>::length();
       _lock.unlock();
       return length;
    }

    bool is_empty() {
        bool empty = false;
        _lock.lock();
        empty = indexed_list<T>::is_empty();
        _lock.unlock();
        return empty;
    }

    int32_t remove(T* value) {
        size_t index = 0;
        _lock.lock();
        index = indexed_list<T>::remove(value);
        _lock.unlock();
        return index;
    }

    T *operator[](size_t index) {
        T *value = NULL;
        _lock.lock();
        value = indexed_list<T>::operator[](index);
        _lock.unlock();
        return value;
    }
};

#endif /* SYNCHRONIZED_INDEXED_LIST_H */
