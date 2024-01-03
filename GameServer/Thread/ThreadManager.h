//
// Created by root on 1/2/24.
//

#ifndef GAMESERVER_THREADMANAGER_H
#define GAMESERVER_THREADMANAGER_H

#include <thread>
#include <functional>
#include "../Core/CoreHeader.h"
class ThreadManager {
public:
    ThreadManager();
    ~ThreadManager();

    void Launch(function<void(void)> callback);
    void Join();

    static void InitTLS();
    static void DestroyTLS();

private:
    Mutex _lock;
    vector<thread> _threads;
};


#endif //GAMESERVER_THREADMANAGER_H
