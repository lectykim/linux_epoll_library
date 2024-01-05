//
// Created by root on 1/2/24.
//

#ifndef GAMESERVER_COREMACRO_H
#define GAMESERVER_COREMACRO_H

#define OUT

#define USE_LOCK Lock _lock;
#define READ_LOCK ReadLockGuard readLockGuard(_lock,typeid(this).name());
#define WRITE_LOCK WriteLockGuard(_lock,typeid(this).name());

#define CRASH(cause) \
{                    \
    exit(-2);                     \
}

#define ASSERT_CRASH(expr) \
{                          \
    if(!(expr))            \
    {                      \
        CRASH("FALSE");                       \
    }                      \
}
#endif //GAMESERVER_COREMACRO_H
