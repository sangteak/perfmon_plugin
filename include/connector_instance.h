#pragma once
#ifndef _CONNECTOR_INSTANCE_H
#define _CONNECTOR_INSTANCE_H

#if TARGET_ID == TARGET_CONNECTOR
// 공유 메모리 이름
#define PerfDataName L"Global\\connector_mmf"

// 레지스터 경로
#define PERFORMANCE_REGISTRY_PATH L"SYSTEM\\CurrentControlSet\\Services\\PerfConnector\\Performance"

// 인스턴스 갯수(인스턴스 변경 시 동기화 필요함)
#define METRICS_COUNT 10

_metrics_name_t<METRICS_COUNT> g_metrics = {
	L"01_PostByte",
	L"02_PostCnt",
	L"03_SendBytes",
	L"04_SendCnt",
	L"05_SendQLen",
	L"06_SentBytes",
	L"07_SentCount",
	L"08_RecvBytes",
	L"09_RecvCount",
	L"10_ErrCount"
};

#endif // end TARGET_ID == TARGET_CONNECTOR

#endif // end _CONNECTOR_INSTANCE_H