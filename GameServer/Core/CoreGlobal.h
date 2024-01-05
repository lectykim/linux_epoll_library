//
// Created by root on 1/2/24.
//

#ifndef GAMESERVER_COREGLOBAL_H
#define GAMESERVER_COREGLOBAL_H


extern class ThreadManager* GThreadManager;
extern class EpollManager* GEpollManager;
extern class CoreGlobal* GCoreGlobal;
extern class Memory* GMemory;
extern class SendBufferManager* GSendBufferManager;
extern class JobQueue* GJobQueue;

#endif //GAMESERVER_COREGLOBAL_H
