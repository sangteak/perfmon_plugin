copy /Y perfmon\connector\*.dll c:\windows\system32
copy /Y perfmon\dbproxy\*.dll c:\windows\system32
copy /Y perfmon\network\*.dll c:\windows\system32
copy /Y perfmon\npc\*.dll c:\windows\system32
copy /Y perfmon\user\*.dll c:\windows\system32
copy /Y perfmon\zone\*.dll c:\windows\system32

regedit /s perfmon\connector\perfconnector.reg
regedit /s perfmon\dbproxy\perfdbproxy.reg
regedit /s perfmon\network\perfnetwork.reg
regedit /s perfmon\npc\perfnpc.reg
regedit /s perfmon\user\perfuser.reg
regedit /s perfmon\zone\perfzone.reg

lodctr perfmon\connector\perfconnector.ini
lodctr perfmon\dbproxy\perfdbproxy.ini
lodctr perfmon\network\perfnetwork.ini
lodctr perfmon\npc\perfnpc.ini
lodctr perfmon\user\perfuser.ini
lodctr perfmon\zone\perfzone.ini

pause