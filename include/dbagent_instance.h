#pragma once
#ifndef _DBAGENT_INSTANCE_H
#define _DBAGENT_INSTANCE_H

#if TARGET_ID == TARGET_CONNECTOR

// ���� �޸� �̸�
#define PerfDataName L"Global\\dbagent_mmf"

// �������� ���
#define PERFORMANCE_REGISTRY_PATH L"SYSTEM\\CurrentControlSet\\Services\\PerfDBAgent\\Performance"

// �ν��Ͻ� ����
#define METRICS_COUNT 3

_metrics_name_t<METRICS_COUNT> g_metrics = {
	L"01RecvMsgCnt",
	L"02SendMsgCnt",
	L"03ProcMsgCnt"
};

#endif // end TARGET_ID == TARGET_CONNECTOR

#endif // end _DBAGENT_INSTANCE_H