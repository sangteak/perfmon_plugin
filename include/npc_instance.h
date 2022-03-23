#pragma once
#ifndef _NPC_INSTANCE_H
#define _NPC_INSTANCE_H

#if TARGET_ID == TARGET_NPC

// 공유 메모리 이름
#define PerfDataName L"Global\\npc_mmf"

// 레지스터 경로
#define PERFORMANCE_REGISTRY_PATH L"SYSTEM\\CurrentControlSet\\Services\\PerfNpc\\Performance"

// 메트릭 수
#define METRICS_COUNT 20

_metrics_name_t<METRICS_COUNT> g_metrics = {
	L"01SendPktCnt",
	L"02RecvPktCnt",
	L"03ZoneCount",
	L"04PktProcTime",
	L"05LogicProcTime",
	L"06AbiUptTime",
	L"07HitUptTime",
	L"08EtyUptTime",
	L"09CrwdMvUptTime",
	L"10EtyMvUptTime",
	L"11AggroUptTime",
	L"12GridUptTime",
	L"13BTUptTime",
	L"14TrriUptTime",
	L"15ZoneID",
	L"16EtyCnt",
	L"17FrmDelayCnt",
	L"18FrmDelayMin",
	L"19FrmDelayMed",
	L"20FrmDelayMax"
};
#endif

#endif // end _NPC_INSTANCE_H