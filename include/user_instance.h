#pragma once
#ifndef _USER_INSTANCE_H
#define _USER_INSTANCE_H

#if TARGET_ID == TARGET_USER

// 공유 메모리 이름
#define PerfDataName L"Global\\user_mmf"

// 레지스터 경로
#define PERFORMANCE_REGISTRY_PATH L"SYSTEM\\CurrentControlSet\\Services\\PerfUser\\Performance"

// 메트릭 수
#define METRICS_COUNT 18

_metrics_name_t<METRICS_COUNT> g_metrics = {
	L"01c2s",
	L"02s2c",
	L"03s2cReal",
	L"04s2cRealLen",
	L"05s2cRealCall",
	L"06c2cReal",
	L"07c2c",
	L"08worker",
	L"09activeCnt",
	L"10rtt_100",
	L"11rtt101_150",
	L"12rtt151_200",
	L"13rtt201_250",
	L"14rtt250_",
	L"15pathFDReq",
	L"16pathFDProc",
	L"17httpReqCnt",
	L"18httpResCnt"
};

#endif

#endif // end _USER_INSTANCE_H