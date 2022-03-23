#pragma once
#ifndef _CONNECTOR_INSTANCE_H
#define _CONNECTOR_INSTANCE_H

#if TARGET_ID == TARGET_CONNECTOR
// ���� �޸� �̸�
#define PerfDataName L"Global\\connector_mmf"

// �������� ���
#define PERFORMANCE_REGISTRY_PATH L"SYSTEM\\CurrentControlSet\\Services\\PerfConnector\\Performance"

// �ν��Ͻ� ����(�ν��Ͻ� ���� �� ����ȭ �ʿ���)
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