#include <iostream>
#include "Core/CoreHeader.h"
#include "Thread/ThreadManager.h"
#include "Core/CoreGlobal.h"
#include "Thread/Lock.h"

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
SimpleLockQueue<int32> simpleLockQueue;
int main() {

    for(int32 i=0;i<3;i++)
    {
        GThreadManager->Launch([](){
            while(true)
            {
                simpleLockQueue.Push(rand()%1000);
                this_thread::sleep_for(1s);
            }
        });
    }

    for(int32 i=0;i<3;i++)
    {
        GThreadManager->Launch([](){
            while(true)
            {
                int32 t = simpleLockQueue.Pop();
                cout << t << endl;
                this_thread::sleep_for(1s);
            }
        });
    }

    GThreadManager->Join();
    return 0;
}
