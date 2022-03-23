#pragma once
#ifndef _NETWORK_INTANCE_H
#define _NETWORK_INTANCE_H

#if TARGET_ID == TARGET_NETWORK
// 공유 메모리 이름
#define PerfDataName L"Global\\network_mmf"

// 레지스터 경로
#define PERFORMANCE_REGISTRY_PATH L"SYSTEM\\CurrentControlSet\\Services\\PerfNetwork\\Performance"

// 인스턴스 갯수
#define METRICS_COUNT 7

_metrics_name_t<METRICS_COUNT> g_metrics = {
	L"01_PostSendByte",
	L"02_PostSendCnt",
	L"03_SendBytes",
	L"04_SendCount",
	L"05_RecvBytes",
	L"06_RecvCount",
	L"07_ErrCount"
};

#endif // end TARGET_ID == TARGET_NETWORK

#endif // end _NETWORK_INTANCE_H