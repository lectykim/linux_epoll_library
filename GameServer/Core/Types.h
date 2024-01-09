//
// Created by root on 1/2/24.
//

#ifndef GAMESERVER_TYPES_H
#define GAMESERVER_TYPES_H

#include <mutex>
#include <atomic>
#include <condition_variable>
#include <memory>
using BYTE = unsigned char;
using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;
using uint8=u_int8_t ;
using uint16 = u_int16_t;
using uint32 = u_int32_t;
using uint64=u_int64_t;

template<typename T>
using Atomic=std::atomic<T>;
using Mutex = std::mutex;
using CondVar = std::condition_variable;
using UniqueLock = std::unique_lock<std::mutex>;
using LockGuard = std::lock_guard<std::mutex>;

#define USING_SHARED_PTR(name)  using name##Ref = std::shared_ptr<class name>;

USING_SHARED_PTR(Job);
USING_SHARED_PTR(JobQueue);
USING_SHARED_PTR(SendBuffer);
USING_SHARED_PTR(SendBufferChunk);
USING_SHARED_PTR(PacketSession);

#define size16(val) static_cast<int16>(sizeof(val));
#define size32(val) static_cast<int32>(sizeof(val));
#define len16(arr)  static_cast<int16>(sizeof(arr)/sizeof(arr[0]));
#define len32(arr)  static_cast<int32>(sizeof(arr)/sizeof(arr[0]));

#endif //GAMESERVER_TYPES_H
