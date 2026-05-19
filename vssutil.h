#ifndef __VSSUTIL_H_GUARD__
#define __VSSUTIL_H_GUARD__

#include <Windows.h>
#include <vss.h>

/**
 * @brief GUID of the IVssCoordinator COM interface: da9f41d4-1a5d-41d0-a614-6dfd78df5d05
*/
CONST IID IID_IVssCoordinator = { 0xda9f41d4, 0x1a5d, 0x41d0, {0xa6, 0x14, 0x6d, 0xfd, 0x78, 0xdf, 0x5d, 0x05} };

/**
 * @brief GUID of the CVssCoordinator class: e579ab5f-1cc4-44b4-bed9-de0991ff0623
*/
CONST IID CLSID_CVssCoordinator = { 0xe579ab5f, 0x1cc4, 0x44b4, {0xbe, 0xd9, 0xde, 0x09, 0x91, 0xff, 0x06, 0x23} };

typedef interface IVssCoordinator IVssCoordinator;

typedef struct VssCoordinatorVtbl {
	BEGIN_INTERFACE

	/**
	 * @brief QueryInterface method from IUnknown
	*/
	HRESULT(STDMETHODCALLTYPE* QueryInterface) (
		_In_  IVssCoordinator* This,
		_In_  REFIID           riid,
		_Out_ PVOID*           ppvObject
	);

	/**
	 * @brief AddRef from IUnknown
	*/
	ULONG(STDMETHODCALLTYPE* AddRef)(
		_In_ IVssCoordinator* This
	);

	/**
	 * @brief Release from IUnknown
	*/
	ULONG(STDMETHODCALLTYPE* Release)(
		_In_ IVssCoordinator* This
	);
	
	/**
	* /!\
	* Everything below this line has been extracted via OleView.Net and VSSVC.exe image.
	* Some of the methods might be wrong 
	* /!\
	*/
	HRESULT(STDMETHODCALLTYPE* SetContext)(
		_In_ IVssCoordinator* This,
		_In_ LONG             p0
	);
	HRESULT(STDMETHODCALLTYPE* StartSnapshotSet)(
		_In_  IVssCoordinator* This,
		_Out_ GUID*            p0
	);
	HRESULT(STDMETHODCALLTYPE* AddToSnapshotSet)(
		_In_  IVssCoordinator* This,
		_In_  WCHAR*           p0,
		_In_  GUID             p1,
		_Out_ GUID*            p2
	);
	HRESULT(STDMETHODCALLTYPE* DoSnapshotSet)(
		_In_  IVssCoordinator* This,
		_In_  IDispatch*       p0,
		_Out_ IVssAsync**      p1
	);
	HRESULT(STDMETHODCALLTYPE* GetSnapshotProperties)(
		_In_  IVssCoordinator*   This,
		_In_  GUID               p0,
		_Out_ VSS_SNAPSHOT_PROP* p1
	);
	HRESULT(STDMETHODCALLTYPE* ExposeSnapshot)(
		_In_  IVssCoordinator* This,
		_In_  GUID             p0,
		_In_  WCHAR*           p1,
		_In_  LONG             p2,
		_In_  WCHAR*           p3,
		_Out_ WCHAR**          p4
	);
	HRESULT(STDMETHODCALLTYPE* ImportSnapshots)(
		_In_  IVssCoordinator* This,
		_In_  USHORT*          p0,
		_Out_ IVssAsync**      p1
	);
	HRESULT(STDMETHODCALLTYPE* Query)(
		_In_  IVssCoordinator* This,
		_In_  GUID             p0,
		_In_  VSS_OBJECT_TYPE  p1,
		_In_  VSS_OBJECT_TYPE  p2,
		_Out_ IVssEnumObject** p3
	);
	HRESULT(STDMETHODCALLTYPE* DeleteSnapshots)(
		_In_  IVssCoordinator* This,
		_In_  GUID             ShadowCopyID,
		_In_  VSS_OBJECT_TYPE  ObjType,
		_In_  INT              p2,
		_Out_ LONG*            p3,
		_Out_ GUID*            p4
	);
	HRESULT(STDMETHODCALLTYPE* BreakSnapshotSet)(
		_In_  IVssCoordinator* This,
		_In_  GUID             p0
	);
	HRESULT(STDMETHODCALLTYPE* RevertToSnapshot)(
		_In_  IVssCoordinator* This,
		_In_  GUID             p0,
		_In_  INT              p1
	);
	HRESULT(STDMETHODCALLTYPE* QueryRevertStatus)(
		_In_  IVssCoordinator* This,
		_In_  WCHAR*           p0,
		_Out_ IVssAsync**      p1
	);
	HRESULT(STDMETHODCALLTYPE* IsVolumeSupported)(
		_In_  IVssCoordinator* This,
		_In_  GUID             p0,
		_In_  WCHAR*           p1,
		_Out_ INT*             p2
	);
	HRESULT(STDMETHODCALLTYPE* IsVolumeSnapshotted)(
		_In_  IVssCoordinator* This,
		_In_  GUID             p0,
		_In_  WCHAR*           p1,
		_Out_ INT*             p2,
		_Out_ LONG*            p3
	);
	HRESULT(STDMETHODCALLTYPE* SetWriterInstance)(
		_In_  IVssCoordinator* This,
		_In_  LONG             p0,
		_Out_ GUID*            p1
	);

	END_INTERFACE
} VssCoordinatorVtbl;

interface IVssCoordinator {
	CONST_VTBL struct VssCoordinatorVtbl* lpVtbl;
};


HRESULT VssUtilListSnapshots(
	_In_  IVssCoordinator*  pIVssCoordinator,
	_Out_ VSS_OBJECT_PROP** ppVssSnapshots,
	_Out_ LONG*             plNumberOfSnapshots
) {
	// 1. Get the IVssEnumObject interface
	IVssEnumObject* pIVssEnumObject = NULL;
	THROW_ON_FAILURE(pIVssCoordinator->lpVtbl->Query(
		pIVssCoordinator,
		GUID_NULL,
		VSS_OBJECT_NONE,
		VSS_OBJECT_SNAPSHOT,
		&pIVssEnumObject
	));

	// 2. Get all the snapshots
	ULONG ulObjects = 0x10;
	ULONG ulFetchedObjects = 0x00;
	*ppVssSnapshots = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(VSS_OBJECT_PROP) * ulObjects);

	THROW_ON_FAILURE(pIVssEnumObject->lpVtbl->Next(
		pIVssEnumObject,
		ulObjects,
		*ppVssSnapshots,
		plNumberOfSnapshots
	));

	for (LONG i = 0; i < *plNumberOfSnapshots; i++) {
		VSS_SNAPSHOT_PROP snap = (*ppVssSnapshots)[i].Obj.Snap;

		// Convert GUIDs to strings
		WCHAR wszSnapshotId[40] = { 0 };
		WCHAR wszSnapshotSetId[40] = { 0 };
		StringFromGUID2(&snap.m_SnapshotId, wszSnapshotId, 40);
		StringFromGUID2(&snap.m_SnapshotSetId, wszSnapshotSetId, 40);

		// Convert timestamp
		FILETIME ft;
		SYSTEMTIME st;
		ft.dwLowDateTime = (DWORD)(snap.m_tsCreationTimestamp);
		ft.dwHighDateTime = (DWORD)(snap.m_tsCreationTimestamp >> 32);
		FileTimeToSystemTime(&ft, &st);

		wprintf(L"\n");
		wprintf(L"Contents of shadow copy set ID: %s\n", wszSnapshotSetId);
		wprintf(L"   Contained 1 shadow copies at creation time: "
			L"%02d/%02d/%04d %02d:%02d:%02d\n",
			st.wDay, st.wMonth, st.wYear,
			st.wHour, st.wMinute, st.wSecond);
		wprintf(L"\n");
		wprintf(L"   Shadow Copy ID:         %s\n", wszSnapshotId);
		wprintf(L"   Original Volume:        %s\n", snap.m_pwszOriginalVolumeName);
		wprintf(L"   Shadow Copy Volume:     %s\n", snap.m_pwszSnapshotDeviceObject);
		wprintf(L"   Originating Machine:    %s\n", snap.m_pwszOriginatingMachine);
		wprintf(L"   Service Machine:        %s\n", snap.m_pwszServiceMachine);
		wprintf(L"   Exposed Name:           %s\n",
			snap.m_pwszExposedName ? snap.m_pwszExposedName : L"(none)");
		wprintf(L"   Exposed Path:           %s\n",
			snap.m_pwszExposedPath ? snap.m_pwszExposedPath : L"(none)");
		wprintf(L"   Provider ID:            ");

		WCHAR wszProviderId[40] = { 0 };
		StringFromGUID2(&snap.m_ProviderId, wszProviderId, 40);
		wprintf(L"%s\n", wszProviderId);
		// Snapshot attributes
		wprintf(L"   Attributes:             ");
		LONG attr = snap.m_lSnapshotAttributes;
		if (attr & VSS_VOLSNAP_ATTR_PERSISTENT)          wprintf(L"Persistent ");
		if (attr & VSS_VOLSNAP_ATTR_CLIENT_ACCESSIBLE)   wprintf(L"Client-accessible ");
		if (attr & VSS_VOLSNAP_ATTR_NO_AUTO_RELEASE)     wprintf(L"No-auto-release ");
		if (attr & VSS_VOLSNAP_ATTR_NO_WRITERS)          wprintf(L"No-writers ");
		if (attr & VSS_VOLSNAP_ATTR_TRANSPORTABLE)       wprintf(L"Transportable ");
		if (attr & VSS_VOLSNAP_ATTR_NOT_SURFACED)        wprintf(L"Not-surfaced ");
		if (attr & VSS_VOLSNAP_ATTR_HARDWARE_ASSISTED)   wprintf(L"Hardware-assisted ");
		if (attr & VSS_VOLSNAP_ATTR_DIFFERENTIAL)        wprintf(L"Differential ");
		if (attr & VSS_VOLSNAP_ATTR_PLEX)                wprintf(L"Plex ");
		if (attr & VSS_VOLSNAP_ATTR_IMPORTED)            wprintf(L"Imported ");
		if (attr & VSS_VOLSNAP_ATTR_EXPOSED_LOCALLY)     wprintf(L"Exposed-locally ");
		if (attr & VSS_VOLSNAP_ATTR_EXPOSED_REMOTELY)    wprintf(L"Exposed-remotely ");
		wprintf(L"\n");

		// Snapshot state
		wprintf(L"   Snapshot State:         ");
		switch (snap.m_eStatus) {
		case VSS_SS_UNKNOWN:             wprintf(L"Unknown\n");           break;
		case VSS_SS_PREPARING:           wprintf(L"Preparing\n");         break;
		case VSS_SS_PROCESSING_PREPARE:  wprintf(L"Processing prepare\n"); break;
		case VSS_SS_PREPARED:            wprintf(L"Prepared\n");          break;
		case VSS_SS_PROCESSING_COMMIT:   wprintf(L"Processing commit\n"); break;
		case VSS_SS_COMMITTED:           wprintf(L"Committed\n");         break;
		case VSS_SS_PROCESSING_POSTCOMMIT: wprintf(L"Post-commit\n");     break;
		case VSS_SS_CREATED:             wprintf(L"Created\n");           break;
		case VSS_SS_ABORTED:             wprintf(L"Aborted\n");           break;
		case VSS_SS_DELETED:             wprintf(L"Deleted\n");           break;
		default:                         wprintf(L"0x%08lx\n",
			snap.m_eStatus);          break;
		}

		wprintf(L"   Snapshot Count:         %ld\n", snap.m_lSnapshotsCount);
		wprintf(L"\n");
	}

	// 3. Cleanup and return.
	pIVssEnumObject->lpVtbl->Release(pIVssEnumObject);
	return S_OK;
}

HRESULT VssUtilDeleteSnapshots(
	_In_  IVssCoordinator* pIVssCoordinator,
	_Out_ VSS_OBJECT_PROP* pVssSnapshots,
	_Out_ LONG             lNumberOfSnapshots
) {
	// 1. Get param ready
	LPWSTR wszShadowCopySetId = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 0x20 * sizeof(WCHAR));
	LPWSTR wszShadowCopyId    = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 0x20 * sizeof(WCHAR));

	// 2. Parse all entries
	while (lNumberOfSnapshots--) {
		VSS_OBJECT_PROP Element = pVssSnapshots[lNumberOfSnapshots];
		if (Element.Type != VSS_OBJECT_SNAPSHOT)
			continue;

		// Get the GUIDs
		RtlZeroMemory(wszShadowCopySetId, 0x20 * sizeof(WCHAR));
		RtlZeroMemory(wszShadowCopyId, 0x20 * sizeof(WCHAR));
		StringFromGUID2(&Element.Obj.Snap.m_SnapshotSetId, wszShadowCopySetId, 0x20 * sizeof(WCHAR));
		StringFromGUID2(&Element.Obj.Snap.m_SnapshotId, wszShadowCopyId, 0x20 * sizeof(WCHAR));

		// Display information
		wprintf(L"Delleting following candidate: \n");
		wprintf(L"\tShadow copy set ID: %s\n", wszShadowCopySetId);
		wprintf(L"\tShadow copy ID:     %s\n\n", wszShadowCopyId);

		// Delete snapshot
		LONG lSomething = 0x00;
		GUID SomethingElse = { 0x00 };
		THROW_ON_FAILURE(pIVssCoordinator->lpVtbl->DeleteSnapshots(
			pIVssCoordinator,
			Element.Obj.Snap.m_SnapshotId,
			VSS_OBJECT_SNAPSHOT,
			1,
			&lSomething,
			&SomethingElse
		));
	}

	// 3. Cleanup and return
	HeapFree(GetProcessHeap(), 0x00, wszShadowCopySetId);
	HeapFree(GetProcessHeap(), 0x00, wszShadowCopyId);
	return S_OK;
}

#endif // !__VSSUTIL_H_GUARD__
