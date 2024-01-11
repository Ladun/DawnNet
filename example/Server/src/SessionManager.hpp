#pragma once

class GameSession;

using GameSessionRef = std::shared_ptr<GameSession>;

using namespace DawnNet;

class SessionManager : public Singleton<SessionManager>
{
public:
    void Add(GameSessionRef session);
    void Remove(GameSessionRef session);
    void BroadCast(SendBufferRef sendBuffer);

private:
    USE_LOCK;
    Set<GameSessionRef> _sessions;
};