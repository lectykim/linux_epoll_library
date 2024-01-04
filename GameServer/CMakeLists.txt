cmake_minimum_required(VERSION 3.27)
project(GameServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREAD_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
add_executable(GameServer main.cpp
        Core/Types.h
        Core/CoreHeader.h
        Thread/ThreadManager.cpp
        Thread/ThreadManager.h
        Core/CoreTLS.cpp
        Core/CoreTLS.h
        Core/CoreGlobal.cpp
        Core/CoreGlobal.h
        Thread/Lock.cpp
        Thread/Lock.h
        Core/CoreMacro.h
        Memory/Allocator.cpp
        Memory/Allocator.h
        Memory/Container.h
        Util/BufferReader.cpp
        Util/BufferReader.h
        Util/BufferWriter.cpp
        Util/BufferWriter.h
        Util/LockQueue.h
        Network/EpollManager.cpp
        Network/EpollManager.h
        Network/SocketManager.cpp
        Network/SocketManager.h
)
target_link_libraries(Threads::Threads)