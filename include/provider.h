#ifndef _PROVIDER_H
#define _PROVIDER_H

#include <windows.h>
#include <strsafe.h>
#include <cstdint>
#include "configuration.h"
#include "mmf.h"
#include "counter_offsets.h"

// 퍼프몬 인터페이스 정의
extern "C" DWORD APIENTRY OpenPerfData(LPWSTR pContext);
extern "C" DWORD APIENTRY CollectPerfData(LPWSTR pQuery, PVOID* ppData, LPDWORD pcbData, LPDWORD pObjectsReturned);
extern "C" DWORD APIENTRY ClosePerfData();

// 기능 함수들
BOOL IsQuerySupported(LPWSTR pQuery, DWORD* pQueriedObjects);
DWORD GetQuerySize(DWORD QueriedObjects);

// 메트릭 이름 최대 길이
#define MAX_INSTANCE_NAME_LEN 15 

// Define the Peer counter object. This object is a multiple
// instance object, so you must define the object and instances
// separately.
typedef struct _peer {
	PERF_OBJECT_TYPE Object;
	PERF_COUNTER_DEFINITION BytesServedCounter;
} PEER, *PPEER;

typedef struct _peerinstance {
	PERF_INSTANCE_DEFINITION Instance;
	WCHAR InstanceName[MAX_INSTANCE_NAME_LEN + 1];
	PERF_COUNTER_BLOCK CounterBlock;
	DWORD BytesServedData;
} PEER_INSTANCE, *PPEER_INSTANCE;

#define NumberOfPeerCounters 1
#define BytesServedOffset sizeof(PERF_COUNTER_BLOCK)
#define EndOfPeerData BytesServedOffset + (sizeof(DWORD) * NumberOfPeerCounters)

typedef enum _queriedflags {
	QUERIED_TRANSFER_OBJECT = 1,
	QUERIED_PEER_OBJECT = 2,
	QUERIED_ALL_OBJECTS = 0xFFFF
} QUERIED_FLAGS;

// Peer object
PEER g_Peer;                     

// Index value for the Peer object
DWORD g_PeerIndex = 0;           

// Objects that were queried
DWORD g_QueriedObjects = 0;      

// Reference count for the number of times
// that OpenPerfData is called.
UNALIGNED LONG g_OpenCount = 0;  

// shared memory object
Mmf g_PerfData;					 

#endif