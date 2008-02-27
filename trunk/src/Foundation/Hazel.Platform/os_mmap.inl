
#if defined (Hazel_HAS_VOIDPTR_MMAP)
typedef void *Hazel_MMAP_TYPE;
#else
typedef char *Hazel_MMAP_TYPE;
#endif /* Hazel_HAS_VOIDPTR_MMAP */

	int madvise (void* addr, size_t len, int map_advice)
	{
		return -1;
	}

	 void* mmap (void *addr,
		size_t len,
		int prot,
		int flags,
		Hazel_HANDLE file_handle,
		off_t off,
		Hazel_HANDLE& file_mapping,
		LPSECURITY_ATTRIBUTES sa,
		const tchar *file_mapping_name)
	{
		if (!Hazel_BIT_ENABLED (flags, MAP_FIXED))
			addr = 0;
		else if (addr == 0)   // can not map to address 0
		{
			errno = EINVAL;
			return 0;
		}

		int nt_flags = 0;

		if (Hazel_BIT_ENABLED (flags, MAP_PRIVATE))
		{
			nt_flags = FILE_MAP_COPY;
		}
		else if (Hazel_BIT_ENABLED (flags, MAP_SHARED))
		{
			if (Hazel_BIT_ENABLED (prot, PAGE_READONLY))
				nt_flags = FILE_MAP_READ;
			if (Hazel_BIT_ENABLED (prot, PAGE_READWRITE))
				nt_flags = FILE_MAP_WRITE;
		}

		if ( file_mapping == Hazel_INVALID_HANDLE)
		{
			int try_create = 1;
			if ((file_mapping_name != 0) && (*file_mapping_name != 0))
			{ // 尝试打开一下，看有没有人创建过了
				file_mapping = OpenFileMapping( nt_flags,
					0,
					file_mapping_name);

				if ( file_mapping != Hazel_INVALID_HANDLE
					|| (::GetLastError () == ERROR_INVALID_NAME
					&& ::GetLastError () == ERROR_FILE_NOT_FOUND))
					try_create = 0;
			}

			if (try_create)
			{
				file_mapping = CreateFileMapping( file_handle,
					sa,
					prot,
					0,
					0,
					file_mapping_name);
			}
		}

		if (file_mapping == 0)
			return 0;

		void *addr_mapping = ::MapViewOfFileEx (file_mapping,
			nt_flags,
			0,
			off,
			len,
			addr);


		///// 临时使用一下，
		//if (file_mapping == &local_handle)
		//	::CloseHandle (*file_mapping);

		if (addr_mapping == 0)
			return 0;
		else
			return addr_mapping;
	}

	 int mprotect (void *addr, size_t len, int prot)
	{
		DWORD dummy; // Sigh!
		return ::VirtualProtect(addr, len, prot, &dummy) ? 0 : -1;
	}

	 int msync (void *addr, size_t len, int sync)
	{
		Hazel_UNUSED_ARG (sync);
		return ::FlushViewOfFile (addr, len)? 0 : -1;

	}

	 int munmap (void *addr, size_t len)
	{
		Hazel_UNUSED_ARG (len);
		return ::UnmapViewOfFile (addr)? 0 : -1;

	}

	 Hazel_HANDLE shm_open (const tchar *filename,
		int prot,
		int flags,
		LPSECURITY_ATTRIBUTES sa)
	{
		int nt_flags = 0;
		if (Hazel_BIT_ENABLED (flags, MAP_PRIVATE))
		{
			nt_flags = FILE_MAP_COPY;
		}
		else if (Hazel_BIT_ENABLED (flags, MAP_SHARED))
		{
			if (Hazel_BIT_ENABLED (prot, PAGE_READONLY))
				nt_flags = FILE_MAP_READ;
			if (Hazel_BIT_ENABLED (prot, PAGE_READWRITE))
				nt_flags = FILE_MAP_WRITE;
		}
		Hazel_UNUSED_ARG (sa);
		return OpenFileMapping( nt_flags , FALSE, filename );
	}

	 int shm_unlink (const tchar *path)
	{
		return -1;
	}
