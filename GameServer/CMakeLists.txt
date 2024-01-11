cmake_minimum_required(VERSION 3.27)
project(GameServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREAD_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/ThirdPartyLib/include/google)
include_directories(${CMAKE_SOURCE_DIR}/ThirdPartyLib/include/hiredis)
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
        Util/BufferReader.cpp
        Util/BufferReader.h
        Util/BufferWriter.cpp
        Util/BufferWriter.h
        Util/LockQueue.h
        Network/EpollManager.cpp
        Network/EpollManager.h
        Network/SocketManager.cpp
        Network/SocketManager.h
        Network/Session.cpp
        Network/Session.h
        Network/SendBuffer.cpp
        Network/SendBuffer.h
        Network/RecvBuffer.cpp
        Network/RecvBuffer.h
        Job/Job.cpp
        Job/Job.h
        Job/JobQueue.cpp
        Job/JobQueue.h
        Memory/Container.h
        Memory/MemoryPool.cpp
        Memory/MemoryPool.h
        Memory/Memory.cpp
        Memory/Memory.h
        Content/SessionManager.cpp
        Content/SessionManager.h
        Content/GameSession.cpp
        Content/GameSession.h
        Content/ClientPacketHandler.cpp
        Content/ClientPacketHandler.h
        Protocol/Protocol.pb.cc
        Protocol/Protocol.pb.h
        Job/PacketQueue.cpp
        Job/PacketQueue.h
        Protocol/Enum.pb.cc
        Protocol/Enum.pb.h
        Content/User.cpp
        Content/User.h
        Content/Room.cpp
        Content/Room.h
        Redis/RedisClient.cpp
        Redis/RedisClient.h
)
target_link_libraries(GameServer ${CMAKE_SOURCE_DIR}/ThirdPartyLib/lib/libprotobuf.a)
target_link_libraries(GameServer ${CMAKE_SOURCE_DIR}/ThirdPartyLib/lib/libhiredis.a)
target_link_libraries(Threads::Threads)