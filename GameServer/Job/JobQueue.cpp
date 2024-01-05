//
// Created by user on 24. 1. 5.
//

#include "JobQueue.h"

void JobQueue::Push(const shared_ptr<Job>& job, bool pushOnly) {
    const int32 prevCount = _jobCount.fetch_add(1);
    _jobs.Push(job);
}

void JobQueue::Execute() {
    if(_jobCount==0)
        return;
    while(true)
    {
        vector<shared_ptr<Job>> jobs;
        _jobs.PopAll(OUT jobs);

        const int32 jobCount = static_cast<int32>(jobs.size());
        for(int32 i=0;i<jobCount;i++)
            jobs[i]->Execute();

        //일감이 0개라면 종료
        if(_jobCount.fetch_sub(jobCount) == jobCount)
            return;
    }
}
