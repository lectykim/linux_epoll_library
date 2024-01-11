//
// Created by user on 24. 1. 10.
//

#ifndef GAMESERVER_REDISCLIENT_H
#define GAMESERVER_REDISCLIENT_H
#include "../Core/CoreHeader.h"
#include "hiredis/hiredis.h"

class RedisClient {
public:
    RedisClient()
    {
        struct timeval timeout = {1,500000};
        //LOCAL
        //context = redisConnectWithTimeout((char*)"127.0.0.1",6379,timeout);
        //ElasticCache
        context = redisConnectWithTimeout((char*)"serverlesschattingserverprivate-t3qdkz.serverless.apn2.cache.amazonaws.com",6379,timeout);
        if(context->err){
            cout << "Connection error" << context->errstr <<endl;
            exit(1);
        }
    }

    ~RedisClient()
    {
        redisFree(context);
    }

public:
    void redisSet(const string& key,const string& value)
    {
        reply = static_cast<redisReply *>(redisCommand(context, "SET %s %s", key.c_str(), value.c_str()));
        freeReplyObject(reply);
    }

    bool redisGet(const string& key,OUT string& value)
    {
        reply = static_cast<redisReply *>(redisCommand(context,"GET %s",key.c_str()));
        if(reply->str == NULL)
        {
            freeReplyObject(reply);
            return false;
            ;
        }
        else
        {
            value = reply->str;
            freeReplyObject(reply);
            return true;
        }

    }


    void redisHashSet(const string& key, const map<string,string>& map)
    {
        vector<const char*>argv;
        vector<size_t> argvLen;

        static char cmd[] = "HMSET";
        argv.push_back(cmd);
        argvLen.push_back(sizeof(cmd)-1);

        argv.push_back(key.c_str());
        argvLen.push_back(key.size());

        std::map<string,string>::const_iterator i;

        for(i=map.begin();i!=map.end();++i)
        {
            argv.push_back(i->first.c_str());
            argvLen.push_back(i->first.size());
            argv.push_back(i->second.c_str());
            argvLen.push_back(i->second.size());
        }

        reply = static_cast<redisReply *>(redisCommandArgv(context, argv.size(), &(argv[0]), &(argvLen[0])));

        freeReplyObject(reply);
    }

    bool redisHashGet(const string& key,OUT map<string,string>& map)
    {
        reply = static_cast<redisReply *>(redisCommand(context,"HGETALL %s",key.c_str()));

        if(reply->type == REDIS_REPLY_ERROR)
        {
            printf("Error : %s",reply->str);
            return false;
        }
        else
        {
            for(int32 i=0;i<reply->elements;i+=2)
            {
                map.insert(std::make_pair(reply->element[i]->str,reply->element[i+1]->str));
            }
            freeReplyObject(reply);
            return true;
        }
    }

private:
    redisContext* context;
    redisReply* reply;
};


#endif //GAMESERVER_REDISCLIENT_H
