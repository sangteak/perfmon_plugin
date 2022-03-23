# PERFMON PLUGIN
PerfMon 사용자 정의 .dll 생성

# 특징
- Perfmon 툴을 이용하여 사용자가 정의한 메트릭을 수집합니다.
- 공유 메모리에 접근하여 정해진 시간 간격마다 데이터를 읽어옵니다.

# 빌드
- C++17 또는 최신 컴파일러 필요
- cmake 3.0 이상 버전 필요
- cmake 빌드(Visual Studio 2019 기준)
```
> cmake -G 를 사용하여 Generators 확인
> cmake ./ -G "Visual Studio 16 2019"
> 솔루션 파일(.sln) 오픈하여 빌드
```

# 설치
1) Register 등록

```console
current path> usercounter.Reg
```

```
REGEDIT4
; file name : usercounter.Reg
;	registry initialization file that installs the Application Memory 
;	performance counters.
;
;		BEFORE RUNNING this file, make sure the APPMEM.DLL has been built and
;		moved into a directory in the system's path, or the correct path has been
;		entered in the Library entry below.
;
[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\PerfUserCounter\Performance]
"Library" = "perfusercounter.dll"
"Open" = "OpenPerfData"
"Collect" = "CollectPerfData"
"Close" = "ClosePerfData"
;
;	the following lines register this app as an event log message provider. This
;	allows the event log to read the message text resource strings from the .DLL
;
[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\EventLog\Application\PerfUserCounter]
"EventMessageFile" = "%systemroot%\\system32\\perfusercounter.dll"
"TypesSupported" = dword:00000007
```

2) .ini 파일 작성 후 lodctr 명령을 통해 등록
```console
current path> lodctr usercounter.ini
```

```
[info]
drivername=PerfUserCounter
symbolfile=CounterOffsets.h

[languages]
009=English

[objects]
PEER_OBJECT_009_NAME=NMSP User Counter

[text]
PEER_OBJECT_009_NAME=NMSP User Counter
PEER_OBJECT_009_HELP=NMSP User Counter Help
BYTES_SERVED_009_NAME=NMSP Bytes Served
BYTES_SERVED_009_HELP=NMSP Bytes Served Help
RESERVE_009_NAME=NMSP Reserve
RESERVE_009_HELP=NMSP Reserve Help
```

3) perfmon 실행하여 Perf User Counter 등록 후 모니터링 시작

# 사용 예
- configuration.h 파일 오픈
```cpp
// ...
#define TARGET_USER_COUNTER 7 // <-- 신규

#define TARGET_ID TARGET_USER_COUNTER // <-- 변경

// ...
```
- [counter name]_instance.h 파일 생성

```cpp
#pragma once
#ifndef _USER_COUNTER_INTANCE_H
#define _USER_COUNTER_INTANCE_H

#if TARGET_ID == TARGET_USER_COUNTER

// 공유 메모리 이름 지정
#define PerfDataName L"Global\\user_counter_mmf" 

// 레지스터 경로 지정
#define PERFORMANCE_REGISTRY_PATH L"SYSTEM\\CurrentControlSet\\Services\\PerfUserCounter\\Performance" 

// 메트릭 갯수 
#define METRICS_COUNT 3

// 메트릭 이름 정의(15글자를 넘어서는 안됨)
_metrics_name_t<METRICS_COUNT> g_metrics = {
	L"01_pktReq",
	L"02_recvBytes",
	L"03_sendBytes"
};

#endif // end TARGET_ID == TARGET_USER_COUNTER

#endif // end _USER_COUNTER_INTANCE_H
```

