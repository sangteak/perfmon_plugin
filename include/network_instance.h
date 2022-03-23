#pragma once
#ifndef _NETWORK_INTANCE_H
#define _NETWORK_INTANCE_H

#if TARGET_ID == TARGET_NETWORK
// ���� �޸� �̸�
#define PerfDataName L"Global\\network_mmf"

// �������� ���
#define PERFORMANCE_REGISTRY_PATH L"SYSTEM\\CurrentControlSet\\Services\\PerfNetwork\\Performance"

// �ν��Ͻ� ����
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