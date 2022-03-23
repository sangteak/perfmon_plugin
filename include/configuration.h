#pragma once
#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

template <int Length>
using _metrics_name_t = std::array<std::wstring, Length>;

template <int Length>
using _metrics_data_t = std::array<int, Length>;

// Å¸°Ù Á¤ÀÇ
#define TARGET_USER			1
#define TARGET_ZONE			2
#define TARGET_NPC			3
#define TARGET_DBAGENT		4
#define TARGET_CONNECTOR	5
#define TARGET_NETWORK		6
#define TARGET_DBPROXY		7

// Å¸°Ù ÁöÁ¤
#define TARGET_ID TARGET_USER

#endif // end _CONFIGURATION_H