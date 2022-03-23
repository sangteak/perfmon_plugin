#pragma once
#ifndef _DBPROXY_INSTANCE_H
#define _DBPROXY_INSTANCE_H

#if TARGET_ID == TARGET_DBPROXY

// ���� �޸� �̸�
#define PerfDataName L"Global\\dbproxy_mmf"

// �������� ���
#define PERFORMANCE_REGISTRY_PATH L"SYSTEM\\CurrentControlSet\\Services\\PerfDBProxy\\Performance"

// �ν��Ͻ� ��
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