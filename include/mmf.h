#pragma once
#ifndef _MMF_H
#define _MMF_H

class Mmf
{
public:
	Mmf()
		: m_handle(nullptr)
		, m_data(nullptr)
		, m_isReadOnly(true)
	{
	}

	~Mmf()
	{
		Close();
	}

	inline bool IsReadOnly() { return m_isReadOnly; }

	DWORD OpenSharedMemory(const wchar_t* name, bool isReadOnly = true)
	{
		m_isReadOnly = isReadOnly;

		auto status = Create(name);
		if (NO_ERROR != status)
		{
			return status;
		}

		return Open();
	}

	void* Read()
	{
		return m_data;
	}

	void Close()
	{
		if (nullptr != m_data)
		{
			UnmapViewOfFile(m_data);
			m_data = nullptr;
		}

		if (nullptr != m_handle)
		{
			CloseHandle(m_handle);
			m_handle = nullptr;
		}

		m_isReadOnly = true;
	}

private:
	DWORD Create(const wchar_t* name)
	{
		auto protect = PAGE_READWRITE;
		if (true == m_isReadOnly)
		{
			protect = PAGE_READONLY;
		}

		m_handle = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, protect, 0, 1024, name);

		auto status = GetLastError();

		if (NO_ERROR != status && ERROR_ALREADY_EXISTS != status)
		{
			Close();
			return status;
		}

		if (nullptr == m_handle)
		{
			return ERROR_INVALID_HANDLE;
		}

		return NO_ERROR;
	}

	DWORD Open()
	{
		auto desiredAccess = FILE_MAP_ALL_ACCESS;
		if (true == m_isReadOnly)
		{
			desiredAccess = FILE_MAP_READ;
		}

		m_data = MapViewOfFile(m_handle, desiredAccess, 0, 0, 0);
		if (nullptr == m_data)
		{
			Close();
			return ERROR_INVALID_DATA;
		}

		return NO_ERROR;
	}

	HANDLE m_handle;
	void* m_data;

	bool m_isReadOnly;
};

#endif // end mmf