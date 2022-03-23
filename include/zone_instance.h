#pragma once
#ifndef _ZONE_INSTANCE_H
#define _ZONE_INSTANCE_H

#if TARGET_ID == TARGET_ZONE

// 공유 메모리 이름
#define PerfDataName L"Global\\zone_mmf"

// 레지스터 경로
#define PERFORMANCE_REGISTRY_PATH L"SYSTEM\\CurrentControlSet\\Services\\PerfZone\\Performance"

// 메트릭 수
#define METRICS_COUNT 26

_metrics_name_t<METRICS_COUNT> g_metrics = {
	L"01SendPktCnt",
	L"02RecvPktCnt",
	L"03ZoneCount",
	L"04MoPktProcTm",
	L"05MoProcTm",
	L"06MoMsgCnt",
	L"07MMOPktProcTm",
	L"08MMOProcTm",
	L"09MMOMsgCnt",
	L"10AbiUptTime",
	L"11HitUptTime",
	L"12EtyUptTime",
	L"13EtyRemTime",
	L"14CwdMvUptTime",
	L"15EtyMvUptTime",
	L"16EtcUptTime",
	L"17FrmDelayCnt",
	L"18FrmDelayMin",
	L"19FrmDelayMedi",
	L"20FrmDelayMax",
	L"21jobQSize",
	L"22jobQNotify",
	L"23pcCount",
	L"24npcCount",
	L"25mmoZoneCount",
	L"26moZoneCount"
};
#endif 

#endif // end _ZONE_INSTANCE_H