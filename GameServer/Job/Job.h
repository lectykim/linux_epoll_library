//
// Created by user on 24. 1. 5.
//

#ifndef GAMESERVER_JOB_H
#define GAMESERVER_JOB_H

#include "../Core/CoreHeader.h"

using CallBackType =std::function<void()>;

class Job {

public:
    Job(CallBackType&&  callBackType):_callback(std::move(callBackType)){}

    template<typename T,typename Ret, typename...Args>
    Job(shared_ptr<T> owner,Ret(T::*memFunc)(Args...),Args&&...args)
    {
        _callback = [owner,memFunc,args...]()
        {
            (owner.get()->*memFunc)(args...);
        };
    }

    void Execute()
    {
        _callback();
    }

private:
    CallBackType _callback;
};


#endif //GAMESERVER_JOB_H
