//
// Created by user on 24. 1. 5.
//

#ifndef GAMESERVER_JOBQUEUE_H
#define GAMESERVER_JOBQUEUE_H
#include "../Core/CoreHeader.h"

class Job;
using CallBackType =std::function<void()>;
class JobQueue :public enable_shared_from_this<JobQueue>{
public:
    void DoAsync(CallBackType&& callBack)
    {
        Push(make_shared<Job>(std::move(callBack)));
    }

    template<typename T,typename Ret, typename... Args>
    void DoAsync(Ret(T::*memFunc)(Args...),Args...args)
    {
        shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
        Push(make_shared<Job>(owner,memFunc,std::forward<Args>(args)...));
    }

    void ClearJobs(){_jobs.Clear();}

public:
    void Push(const shared_ptr<Job>& job,bool pushOnly = false);
    void Execute();

protected:
    SimpleLockQueue<shared_ptr<Job>> _jobs;
    Atomic<int32> _jobCount;
};


#endif //GAMESERVER_JOBQUEUE_H
