#include <string>
#include <array>
#include "provider.h"
#include "connector_instance.h"
#include "dbagent_instance.h"
#include "dbproxy_instance.h"
#include "network_instance.h"
#include "npc_instance.h"
#include "user_instance.h"
#include "zone_instance.h"

// Callback that the performance service calls once for each consumer that wants 
// to consume one or more of your counters. You can use this notification to 
// prepare the counter data structures and setup communications with the 
// application that is providing the actual performance data.
extern "C" DWORD APIENTRY OpenPerfData(LPWSTR pContext)
{
	DWORD FirstCounterIndex = 0;
	DWORD FirstHelpIndex = 0;
	DWORD DataSize = sizeof(DWORD);  // Used in the RegQueryValueEx call
	HKEY hkey;
	LONG rc = ERROR_SUCCESS;

	// Use g_OpenCount to prevent initializing the data more than once.

	if (g_OpenCount > 1)
	{
		//goto cleanup;
		return rc;
	}

	// Retrieve the application specific context data
	// if you define an Export value under the 
	// HKLM\SYSTEM\CurrentControlSet\Services\MyProvider\Linkage key.
	// The context string is a REG_MULTI_SZ string.

	if (pContext)
	{
		for (; *pContext; pContext += (wcslen(pContext) + 1))
		{
			// Do something with the string.
		}
	}
	
	rc = g_PerfData.OpenSharedMemory(PerfDataName, false);
	if (ERROR_SUCCESS != rc)
	{
		//rc = ERROR_SUCCESS;
		//goto cleanup;
		return ERROR_SUCCESS;
	}
	
	// Retrieve the starting index values for your counters and help strings. You add 
	// your offset values (see Adding Counter Names and Descriptions to the Registry)
	// to these index values to determine your actual object and counter index values.

	rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, PERFORMANCE_REGISTRY_PATH, 0, KEY_READ, &hkey);
	if (ERROR_SUCCESS == rc)
	{
		rc = RegQueryValueEx(hkey, L"First Counter", NULL, NULL, (LPBYTE)&FirstCounterIndex, &DataSize);
		if (ERROR_SUCCESS == rc)
		{
			rc = RegQueryValueEx(hkey, L"First Help", NULL, NULL, (LPBYTE)&FirstHelpIndex, &DataSize);
		}

		RegCloseKey(hkey);
	}

	// If you could not open the key or retrieve the value, exit.

	if (ERROR_SUCCESS != rc)
	{
		// If you return a non-success code, the service adds a Disable Performance 
		// Counters value to your Performance key to disable your provider.
		// Consider logging an event and returning success instead of failing.

		//rc = ERROR_SUCCESS;
		return ERROR_SUCCESS;
		//goto cleanup;
	}

	// Initialize the Peer object. This is a multiple instance object. You cannot 
	// initialize all members of the Peer object because you do not know how 
	// many instances there will be until the object data is queried. You set 
	// the TotalByteLength and NumInstances members in the CollectPerfData function.

	ZeroMemory(&g_Peer, sizeof(PEER));
	g_Peer.Object.DefinitionLength = sizeof(PERF_OBJECT_TYPE) + (sizeof(PERF_COUNTER_DEFINITION) * NumberOfPeerCounters);
	g_Peer.Object.HeaderLength = sizeof(PERF_OBJECT_TYPE);
	g_PeerIndex = FirstCounterIndex + PEER_OBJECT;
	g_Peer.Object.ObjectNameTitleIndex = g_PeerIndex;
	g_Peer.Object.ObjectHelpTitleIndex = FirstHelpIndex + PEER_OBJECT;
	g_Peer.Object.DetailLevel = PERF_DETAIL_NOVICE;
	g_Peer.Object.NumCounters = NumberOfPeerCounters;
	g_Peer.Object.DefaultCounter = -1;  // No default counter
	g_Peer.Object.NumInstances = PERF_NO_INSTANCES;
										// Initialize the bytes served counter.

	PEER_INSTANCE inst;
	auto HeaderSize = sizeof(inst.Instance) + sizeof(inst.InstanceName);

	g_Peer.BytesServedCounter.ByteLength = sizeof(PERF_COUNTER_DEFINITION);
	g_Peer.BytesServedCounter.CounterNameTitleIndex = FirstCounterIndex + BYTES_SERVED;
	g_Peer.BytesServedCounter.CounterHelpTitleIndex = FirstHelpIndex + BYTES_SERVED;
	g_Peer.BytesServedCounter.DetailLevel = PERF_DETAIL_NOVICE;
	g_Peer.BytesServedCounter.CounterType = PERF_COUNTER_RAWCOUNT;
	g_Peer.BytesServedCounter.CounterSize = sizeof(inst.BytesServedData);
	g_Peer.BytesServedCounter.CounterOffset = (DWORD)((LPBYTE)& inst.BytesServedData - (LPBYTE)& inst) - HeaderSize;
	
	InterlockedIncrement(&g_OpenCount);  // Decremented in ClosePerfData

	return ERROR_SUCCESS;
}

// Callback that the performance service calls when the consumer wants to sample
// your counter data. Get the counter data and return it to the consumer.
extern "C" DWORD APIENTRY CollectPerfData(LPWSTR pQuery,
	LPVOID* ppData,
	LPDWORD pcbData,
	LPDWORD pObjectsReturned)
{
	BOOL fQuerySupported = FALSE;
	DWORD TotalQuerySize = 0;
	PBYTE pObjects = (PBYTE)*ppData;  // Used to add counter objects to the buffer.
	PEER_INSTANCE inst;

	*pObjectsReturned = 0;

	if (0 == g_OpenCount) // Open did not successfully initialize
	{
		*pcbData = 0;
		*pObjectsReturned = 0;
		return ERROR_SUCCESS;
	}

	// Confirm that we support the requested objects. The query string is passed 
	// to this function as it was passed to RegQueryValueEx. For this example,
	// it should never be the case that we are being asked for objects that
	// we do not support because we included the [objects] section in the .ini file.
	fQuerySupported = IsQuerySupported(pQuery, &g_QueriedObjects);
	if (fQuerySupported == FALSE)
	{
		*pcbData = 0;
		*pObjectsReturned = 0;
		return ERROR_SUCCESS;
	}
	
	// If multiple instance objects are queried, you need to discover how many
	// instances exist so you can determine the buffer size that the 
	// query requires. This value can potentially change from query to query.
	// The Peer object is a multiple instance object. For this example,
	// set the number of instances to 2 if the Peer object was queried.

	if (QUERIED_PEER_OBJECT == (g_QueriedObjects & QUERIED_PEER_OBJECT))
	{
		g_Peer.Object.NumInstances = METRICS_COUNT;
		g_Peer.Object.TotalByteLength = sizeof(PEER) + (sizeof(PEER_INSTANCE) * g_Peer.Object.NumInstances);
	}

	// Check pcbData to see if ppData is large enough to hold our counters.
	// If the buffer is not large enough, return ERROR_MORE_DATA. This tells 
	// the calling application to increase the buffer size and query again.

	TotalQuerySize = GetQuerySize(g_QueriedObjects);
	if (TotalQuerySize > *pcbData)
	{
		*pcbData = 0;
		*pObjectsReturned = 0;
		return ERROR_MORE_DATA;
	}
	else
	{
		*pcbData = TotalQuerySize;
	}

	// If the query includes the Peer object, collect the counter data
	// for the Peer object and its instances and copy it to the ppData buffer.

	if (QUERIED_PEER_OBJECT == (g_QueriedObjects & QUERIED_PEER_OBJECT))
	{
		// Copy the object and counter definition pieces to the buffer,
		// the instance data follows.

		memcpy((PPEER)pObjects, &g_Peer, sizeof(PEER));
		pObjects += sizeof(PEER);

		// Initialize the instance information.
		
		ZeroMemory(&inst, sizeof(PEER_INSTANCE));
		inst.Instance.ByteLength = sizeof(PERF_INSTANCE_DEFINITION) + sizeof(inst.InstanceName);
		inst.Instance.UniqueID = PERF_NO_UNIQUE_ID;
		inst.Instance.NameOffset = sizeof(PERF_INSTANCE_DEFINITION);
		inst.CounterBlock.ByteLength = EndOfPeerData;
		
		// Instance-specific data for the first instance. This information is
		// hard coded for this example.

		auto pointer = g_PerfData.Read();
		if (nullptr == pointer)
		{
			*pcbData = 0;
			*pObjectsReturned = 0;
			return ERROR_SUCCESS;
		}

		_metrics_data_t<METRICS_COUNT> data;
		data.fill(0x00);

		memcpy(reinterpret_cast<char*>(data.data()), reinterpret_cast<char*>(pointer), data.size() * sizeof(_metrics_data_t<METRICS_COUNT>::value_type));

		size_t charSize = sizeof(_metrics_name_t<METRICS_COUNT>::value_type::value_type);

		for (int32_t i = 0; i < g_metrics.size(); ++i)
		{
			inst.Instance.NameLength = g_metrics[i].length() * charSize + charSize;
			StringCchCopy(inst.InstanceName, MAX_INSTANCE_NAME_LEN + 1, g_metrics[i].c_str());

			inst.BytesServedData = data[i];

			memcpy((PPEER_INSTANCE)pObjects, &inst, sizeof(PEER_INSTANCE));
			pObjects += sizeof(PEER_INSTANCE);
		}

		(*pObjectsReturned)++;
	}

	*ppData = (LPVOID)pObjects;

	return ERROR_SUCCESS;
}


// Scan the query string to see if we support the objects.
BOOL IsQuerySupported(LPWSTR pQuery, DWORD* pQueriedObjects)
{
	BOOL fSupported = FALSE;
	WCHAR IndexString[33 + 1];
	LPWSTR pCopy = NULL;
	DWORD dwQueryLen = 0;

	*pQueriedObjects = 0;

	// Copy the query string and make it lowercase.

	dwQueryLen = wcslen(pQuery) + 1;
	pCopy = new WCHAR[dwQueryLen];
	wcscpy_s(pCopy, dwQueryLen, pQuery);
	_wcslwr_s(pCopy, dwQueryLen);

	if (wcsstr(pCopy, L"global"))
	{
		fSupported = TRUE;
		*pQueriedObjects |= QUERIED_ALL_OBJECTS;
	}
	else
	{
		// See if the query contains the index value for
		// the Peer object.
		_ultow_s(g_PeerIndex, IndexString, 33, 10);
		if (wcsstr(pCopy, IndexString))
		{
			fSupported = TRUE;
			*pQueriedObjects |= QUERIED_PEER_OBJECT;
		}
	}

	if (pCopy)
		delete pCopy;

	return fSupported;
}


// Determine the required buffer size for the query.
DWORD GetQuerySize(DWORD QueriedObjects)
{
	DWORD QuerySize = 0;

	if (QUERIED_PEER_OBJECT == (g_QueriedObjects & QUERIED_PEER_OBJECT))
		QuerySize += g_Peer.Object.TotalByteLength;

	return QuerySize;
}

// Callback that the performance service calls once for each consumer that has
// finished consuming your performance counters. Cleanup any resources that 
// you allocated for your performance counters.
extern "C" DWORD APIENTRY ClosePerfData(void)
{
	if (g_OpenCount > 0)
	{
		InterlockedDecrement(&g_OpenCount);
	}

	return ERROR_SUCCESS;
}