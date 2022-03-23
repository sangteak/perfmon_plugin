1. 준비
	- 레지스트리에 등록을 위한 파일 생성
	ex)
		REGEDIT4

		[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\[이름]\Performance]
		"Library" = "[이름].dll"

		; 열기, 수집, 닫기 구현 메소드명 연결
		"Open" = "OpenPerfData"
		"Collect" = "CollectPerfData"
		"Close" = "ClosePerfData"

		[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\EventLog\Application\[이름]]
		"EventMessageFile" = "%systemroot%\\system32\\[이름].dll"
		"TypesSupported" = dword:00000007
		
	- .Ini 파일 준비
	ex)
		[info]
		drivername=[이름]
		symbolfile=[심볼 파일 명]

		[languages]
		009=English

		[objects]
		; 대표 이름
		PEER_OBJECT_009_NAME=NMSP Peer Object

		[text]
		; 추가 테스트 정보
		PEER_OBJECT_009_NAME=NMSP Peer Object
		PEER_OBJECT_009_HELP=NMSP Peer Object Help
		BYTES_SERVED_009_NAME=NMSP Bytes Served
		BYTES_SERVED_009_HELP=NMSP Bytes Served Help
		RESERVE_009_NAME=NMSP Reserve
		RESERVE_009_HELP=NMSP Reserve Help

	
	- 심볼 파일
	ex)
		#ifndef _COUNTER_OFFSETS_H
		#define _COUNTER_OFFSETS_H

		#define PEER_OBJECT		0
		#define BYTES_SERVED	2
		#define RESERVE			4

		#endif

2. 설치
	1) .dll을 windows/system32에 복사
	2) regedit *.reg
	3) lodctr *.ini

3. 실행
	- perfmon 실행
	- Add..
	- 자신이 등록된 objects 이름 확인
	- 추가하여 모니터링 진행

