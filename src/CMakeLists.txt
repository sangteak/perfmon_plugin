# create .exe
#add_executable(my_exe
#	main.cpp
#	mmf.cpp
#)

# create static (.a, .lib)
#add_library(my_lib	STATIC
#	main.cpp
#	mmf.cpp
#)	

# create shared (.so, .dll)
add_library(perfmon_plugin	SHARED
	provider.cpp
	perfmon_plugin.def
)	

target_include_directories(perfmon_plugin
PUBLIC
	${CMAKE_SOURCE_DIR}/include
)

if(MSVC)	# Microsoft Visual C++ Compiler
	target_compile_options(perfmon_plugin
	PUBLIC
		/std:c++latest	/W4	# MSVC 가 식별 가능한 옵션을 지정
	)	
endif()

if(MSVC)	# Microsoft Visual C++ Compiler
	target_compile_definitions(perfmon_plugin
	PRIVATE
		NOMINMAX
		_CRT_SECURE_NO_WARNINGS
		_UNICODE
		UNICODE
	)	
endif()