//
// Created by root on 1/3/24.
//

#ifndef GAMESERVER_LOCKQUEUE_H
#define GAMESERVER_LOCKQUEUE_H
#include "../Core/CoreHeader.h"

template<typename T>
class SimpleLockQueue
{
public:
    void Push(T item)
    {
        WriteLockGuard writeLockGuard(_lock,typeid(this).name());
        _items.push(item);
    }

    T Pop()
    {
        WriteLockGuard writeLockGuard(_lock,typeid(this).name());
        if(_items.empty())
            return T();

        T ret = _items.front();
        _items.pop();
        return ret;
    }

    void PopAll(OUT vector<T>& items)
    {
        WriteLockGuard writeLockGuard(_lock,typeid(this).name());
        while(1)
        {
            if(_items.empty())
                return;
            else
            {
                T item = _items.front();
                _items.pop();
                items.push_back(item);
            }

        }
    }

    void Clear()
    {
        WriteLockGuard writeLockGuard(_lock,typeid(this).name());
        _items = queue<T>();
    }

private:
    Lock _lock;
    queue<T> _items;
};


#endif //GAMESERVER_LOCKQUEUE_H
