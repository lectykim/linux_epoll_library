//
// Created by user on 24. 1. 8.
//

#include "ClientPacketHandler.h"
#include "GameSession.h"
#include "../Redis/RedisClient.h"
#include "User.h"
#include "Room.h"
PacketHandlerFunc GPacketHandler[UINT16_MAX];
bool Handle_INVALID(PacketSessionRef& session,BYTE* buffer,int32 len)
{

    cout << "Invalid call"<<endl;

    return false;
}

bool Handle_C_SIGNUP(PacketSessionRef& session,Protocol::C_SIGNUP& pkt)
{
    GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

    string id = pkt.id();
    string keyCheck;
    Protocol::S_SIGNUP signupPkt;
    auto* returnMessage = new Protocol::ReturnMessage();
    if(!GRedisClient->redisGet(id,keyCheck))
    {
        map<string,string> map;
        map.insert(std::make_pair("pw",pkt.pw()));
        map.insert(std::make_pair("name",pkt.name()));
        map.insert(std::make_pair("type","0"));
        GRedisClient->redisHashSet(id,map);
        returnMessage->set_success(true);
    }
    else
    {
        returnMessage->set_success(false);
        //코드 1: 이미 등록된 사용자입니다.
        returnMessage->set_code(1);
    }
    signupPkt.set_allocated_return_message(returnMessage);
    auto sendBuffer = ClientPacketHandler::MakeSendBuffer(signupPkt);
    session->Send(sendBuffer);
    return false;
}
bool Handle_C_LOGIN(PacketSessionRef& session,Protocol::C_LOGIN& pkt)
{
    GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

    Protocol::S_LOGIN loginPkt;
    auto* returnMessage = new Protocol::ReturnMessage();
    static Atomic<uint64> idGenerator=0;
    map<string,string> outMap;
    if(GRedisClient->redisHashGet(pkt.id(),outMap))
    {
        if(outMap.find("pw")->second == pkt.pw())
        {
            Protocol::UserInfo* userInfo = new Protocol::UserInfo();
            UserRef user = MakeShared<User>();
            user->userSeq = idGenerator++;
            user->name = outMap.find("name")->second;
            user->ownerSession = gameSession;
            user->type = static_cast<Protocol::PlayerType>(std::stoi(outMap.find("type")->second));

            userInfo->set_name(user->name);
            userInfo->set_player_type(user->type);
            userInfo->set_user_code(user->userSeq);

            loginPkt.set_allocated_user_info(userInfo);
            returnMessage->set_success(true);
            gameSession->_user = user;
        }
        else
        {
            //실패코드 3: 해당 비밀번호는 일치하지 않음.
            returnMessage->set_code(3);
            returnMessage->set_success(false);
        }
    }
    else
    {
        //실패코드 2: 해당 id가 존재하지 않음.
        returnMessage->set_code(2);
        returnMessage->set_success(false);
    }
    loginPkt.set_allocated_return_message(returnMessage);

    auto sendBuffer = ClientPacketHandler::MakeSendBuffer(loginPkt);
    session->Send(sendBuffer);
    return false;
}
bool Handle_C_ENTER_GAME(PacketSessionRef& session,Protocol::C_ENTER_GAME& pkt)
{
    GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
    Protocol::ReturnMessage* returnMessage = new Protocol::ReturnMessage();
    Protocol::S_ENTER_GAME enterGamePkt;

    if(gameSession->_user == nullptr)
    {
        //실패코드 4: 로그인 먼저 해 주세요.
        returnMessage->set_code(4);
        returnMessage->set_success(false);
    }
    else
    {
        returnMessage->set_success(true);
        gameSession->_room = GRoom;
        GRoom->Enter(gameSession->_user);
    }

    enterGamePkt.set_allocated_return_message(returnMessage);

    auto sendBuffer = ClientPacketHandler::MakeSendBuffer(enterGamePkt);
    session->Send(sendBuffer);
    return false;
}
bool Handle_C_CHAT(PacketSessionRef& session,Protocol::C_CHAT& pkt)
{
    Protocol::S_CHAT chatPkt;
    auto* returnMessage = new Protocol::ReturnMessage();
    GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

    if(gameSession->_user != nullptr)
    {

        UserRef user = gameSession->_user;

        returnMessage->set_success(true);
        Protocol::UserInfo* userInfo = new Protocol::UserInfo;
        userInfo->set_user_code(user->userSeq);
        userInfo->set_player_type(user->type);
        userInfo->set_name(user->name);
        chatPkt.set_allocated_user_info(userInfo);
        chatPkt.set_msg(pkt.msg());
        cout << "Message : " << pkt.msg() << endl;
        chatPkt.set_allocated_return_message(returnMessage);
        auto sendBuffer = ClientPacketHandler::MakeSendBuffer(chatPkt);
        gameSession->_room.lock()->Broadcast(sendBuffer);


        return false;

    }
    else
    {
        returnMessage->set_code(4);
        returnMessage->set_success(false);
        chatPkt.set_allocated_return_message(returnMessage);
        auto sendBuffer = ClientPacketHandler::MakeSendBuffer(chatPkt);
        session->Send(sendBuffer);
        return false;
    }
}
bool Handle_C_CREATE_ROOM(PacketSessionRef& session,Protocol::C_CREATE_ROOM& pkt)
{
    Protocol::S_CREATE_ROOM createRoomPkt;
    GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
    Protocol::ReturnMessage* returnMessage = new Protocol::ReturnMessage;
    if(gameSession->_user == nullptr)
    {
        returnMessage->set_success(false);
        returnMessage->set_code(4);
    }
    else if(gameSession->_room.lock() != GRoom)
    {
        //실패코드 5: 이미 방에 소속되어 있습니다.
        returnMessage->set_code(5);
        returnMessage->set_success(false);
    }
    else
    {
        uint64 masterUserId = gameSession->_user->userSeq;

        static Atomic<uint64> roomIdGenerator=1;

        RoomRef room = MakeShared<Room>();
        room->roomId = roomIdGenerator++;
        room->roomName = pkt.room_name();
        room->pw = pkt.pw();
        room->masterId = masterUserId;

        gameSession->_user->ownerSession.lock()->_room = room;
        GRoomMap->insert({room->roomId,room});
        GRoom->Leave(gameSession->_user);
        room->Enter(gameSession->_user);

        returnMessage->set_success(true);
        createRoomPkt.set_room_num(room->roomId);
    }

    createRoomPkt.set_allocated_return_message(returnMessage);
    auto sendBuffer = ClientPacketHandler::MakeSendBuffer(createRoomPkt);
    session->Send(sendBuffer);

    return false;
}
bool Handle_C_ENTER_ROOM(PacketSessionRef& session,Protocol::C_ENTER_ROOM& pkt)
{
    Protocol::S_ENTER_ROOM enterRoomPkt;
    GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
    Protocol::ReturnMessage* returnMessage = new Protocol::ReturnMessage();

    if(gameSession->_user == nullptr)
    {
        returnMessage->set_success(false);
        returnMessage->set_code(4);
    }
    else if(gameSession->_user->ownerSession.lock()->_room.lock() != GRoom)
    {
        returnMessage->set_success(false);
        returnMessage->set_code(5);
    }
    else
    {
        if(GRoomMap->find(pkt.room_num())!=GRoomMap->end())
        {
            RoomRef room = GRoomMap->find(pkt.room_num())->second;
            gameSession->_user->ownerSession.lock()->_room = room;
            GRoom->Leave(gameSession->_user);
            room->Enter(gameSession->_user);
            returnMessage->set_success(true);
            enterRoomPkt.set_room_num(pkt.room_num());
        }
        else
        {
            returnMessage->set_success(false);
            // 실패코드 6: 일치하는 방 번호가 없습니다.
            returnMessage->set_code(6);
        }
    }
    enterRoomPkt.set_allocated_return_message(returnMessage);
    auto sendBuffer = ClientPacketHandler::MakeSendBuffer(enterRoomPkt);
    session->Send(sendBuffer);


    return false;
}
bool Handle_C_BAN_OTHER_USER(PacketSessionRef& session,Protocol::C_BAN_OTHER_USER& pkt)
{
    Protocol::S_BAN_OTHER_USER banPkt;
    GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
    Protocol::ReturnMessage * returnMessage = new Protocol::ReturnMessage;
    if(gameSession->_user == nullptr)
    {
        returnMessage->set_success(false);
        returnMessage->set_code(4);
    }
    else
    {
        //현재 세션의 pk가 master id라면 강퇴 권한이 있음.
        if(gameSession->_user->userSeq == gameSession->_user->ownerSession.lock()->_room.lock()->masterId)
        {
            UserRef targetUser = gameSession->_user->ownerSession.lock()->_room.lock()->_users[pkt.target_user_num()];
            gameSession->_user->ownerSession.lock()->_room.lock()->Leave(targetUser);
            GRoom->Enter(targetUser);
            returnMessage->set_success(true);
            Protocol::S_IS_BANNED bannedPkt;
            bannedPkt.set_room_num(gameSession->_user->ownerSession.lock()->_room.lock()->roomId);
            auto noticeBuffer = ClientPacketHandler::MakeSendBuffer(bannedPkt);
            targetUser->ownerSession.lock()->Send(noticeBuffer);
        }
        else
        {
            //실패코드 7: 권한이 없습니다.
            returnMessage->set_success(false);
            returnMessage->set_code(7);
        }
    }

    banPkt.set_allocated_return_message(returnMessage);
    auto sendBuffer = ClientPacketHandler::MakeSendBuffer(banPkt);
    session->Send(sendBuffer);
    return false;
}