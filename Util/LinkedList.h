#pragma once
/**
* Take care this list is for a maximum of 255!
* Else it's counter isnt valid!
*/
#include "cpp_util.h"
template <typename T>
class LinkedList
{
private:
    struct Node
    {
        Node *prev;
        Node *next;
        T value;
    };

    Node *last;
    Node *first;
    short count;

public:
    LinkedList()
    {
        count = -1; //empty
    };

    ~LinkedList()
    {
        if (count > -1)
        {
            clear();
        }
    };
    /** adds to list*/
    inline void add(T t);

    /**removes the thing at index*/
    inline T remove(int index);

    /** Returns NULL(ptr) if index is out of range or item not found somehow*/
    inline T get(int index);

    inline void clear();

    /**Returns the first obj*/
    inline T getFirst();

    /**Returns the last obj*/
    inline T getLast();

    /**Returns the current size. If -1 its empty!*/
    inline int size()
    {
        return count;
    };

    T operator[](const int i)
    {
        return get(i);
    };
};

template <typename T>
inline void LinkedList<T>::add(T t)
{
    Node *n = new Node();
    n->value = t;
    if (count > -1)
    {
        n->next = first;
        n->prev = last;
        last->next = n;
        last = n;
        count++;
    }
    else if (count == -1)//first element
    {
        first = n;
        first->next = n;
        first->prev = n;
        last = n;
        last->next = n;
        last->prev = n;
        count++;
    }
}

template <typename T>
inline T LinkedList<T>::remove(int index)
{
    if (index <= count)
    {
        Node *n = last;
        for (int i = 0; i <= index; i++)
        {
            n = n->next;
        }
        n->prev->next = n->next;
        n->next->prev = n->prev;
        count--;
        return n->value; //return the value of that node
    }
}

template <typename T>
inline T LinkedList<T>::get(int index)
{
    if (index <= count && index > -1)
    {
        Node *n = first;
        int i = 0;
        while (i < index)
        {
            n = n->next;
            i++;
        }
        return n->value;
    }
    return 0;
}

template <typename T>
inline void LinkedList<T>::clear()
{
    Node *n = first;
    while (count > 0)
    {
        Node *toBeDeleted = n;
        n = n->next;
        delete toBeDeleted;
        count--;
    }
}
/**Returns the first obj*/
template <typename T>
inline T LinkedList<T>::getFirst()
{
    return first->value;
};

/**Returns the last obj*/
template <typename T>
inline T LinkedList<T>::getLast()
{
    return last->value;
};