#pragma once
#ifndef _DBAGENT_INSTANCE_H
#define _DBAGENT_INSTANCE_H

#if TARGET_ID == TARGET_CONNECTOR

// 공유 메모리 이름
#define PerfDataName L"Global\\dbagent_mmf"

// 레지스터 경로
#define PERFORMANCE_REGISTRY_PATH L"SYSTEM\\CurrentControlSet\\Services\\PerfDBAgent\\Performance"

// 인스턴스 갯수
#define METRICS_COUNT 3

_metrics_name_t<METRICS_COUNT> g_metrics = {
	L"01RecvMsgCnt",
	L"02SendMsgCnt",
	L"03ProcMsgCnt"
};

#endif // end TARGET_ID == TARGET_CONNECTOR

#endif // end _DBAGENT_INSTANCE_H