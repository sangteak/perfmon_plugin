#pragma once
#ifndef _DBPROXY_INSTANCE_H
#define _DBPROXY_INSTANCE_H

#if TARGET_ID == TARGET_DBPROXY

// 공유 메모리 이름
#define PerfDataName L"Global\\dbproxy_mmf"

// 레지스터 경로
#define PERFORMANCE_REGISTRY_PATH L"SYSTEM\\CurrentControlSet\\Services\\PerfDBProxy\\Performance"

// 인스턴스 수
#define METRICS_COUNT 5

_metrics_name_t<METRICS_COUNT> g_metrics = {
	L"01ProductCnt",
	L"02ConsumeCnt",
	L"03ExecCnt",
	L"04AvgExecTime",
	L"05MaxExectime"
};

#endif // end TARGET_ID == TARGET_DBPROXY

#endif // end _DBPROXY_INSTANCE_H