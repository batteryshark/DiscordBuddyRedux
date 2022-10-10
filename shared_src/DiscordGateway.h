#pragma once
#include "WsClientLib.hpp"
#include "cJSON.h"

enum ActivityType {
	PLAYING,
	STREAMING,
	LISTENING,
	WATCHING,
	CUSTOM,
	COMPLETING
};

enum PacketType {
	OP_DISPATCH,
	OP_HEARTBEAT,
	OP_IDENTIFY,
	OP_PRESENCE,
	OP_VOICE,
	OP_UNUSED_5,
	OP_RESUME,
	OP_RECONNECT,
	OP_GUILD,
	OP_INVALID,
	OP_HELLO,
	OP_HEARTBEAT_ACK
};


class DiscordGateway {
private:
	char _token[128];
	char _url[128];
	char _session_id[128];
	int _running;
	int _heartbeat;
	int _last_seq;
	int _can_resume;
	void* _heartbeat_thread_func;
	void* _gateway_thread_func;

public:
	DiscordGateway(const char* url, const char* token, void* heartbeat_thread_func, void* gateway_thread_func);
	~DiscordGateway();
	int GetHeartbeat();
	int GetLastSeq();
	void SetHeartbeat(int val);
	void SetLastSeq(int val);
	void SendHeartbeat();
	void SendIdentify();
	void ProcessHelloPacket(cJSON* packet);
	void ProcessDispatchPacket(cJSON* packet);
	void SendPacket(cJSON* packet);
	void ProcessReconnectPacket(cJSON* packet);
	void ProcessInvalidSessionPacket(cJSON* packet);
	void ProcessHeartbeatAckPacket(cJSON* packet);
	void SendClearActivity();
	void SetActivity(const char* name, const char* state, const char* details, unsigned long long app_id, const char* large_image, const char* large_text);
	int IsRunning();
	void SetRunning(int val);
	int Start();
	int Stop();
	int Restart();
	int GetState();
	int Connect();
	void Transact(void* handle_err_func, void* handle_receive_func);
};


cJSON* CreateHeartbeatPacket();
cJSON* CreateIdentifyPacket(const char* token);
cJSON* CreateActivityPacket(const char* name, const char* state, const char* details, unsigned long long app_id, const char* large_image, const char* large_text);
cJSON* CreateClearActivityPacket();
cJSON* CreateUpdateVoiceStatePacket();
cJSON* CreateResumePacket(const char* token, const char* session_id, int last_seq);
cJSON* CreateGuildInfoPacket();