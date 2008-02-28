

#ifndef MMAP_H
#define MMAP_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"
#include "Hazel.Platform/os_mmap.h"

_networks_begin

class Hazel_Mem_MAP
{
public:
	Hazel_Mem_MAP (void);

	Hazel_Mem_MAP (Hazel_HANDLE handle,
		int length = -1,
		int prot = PROT_RDWR,
		int share = Hazel_MAP_PRIVATE,
		void *addr = 0,
		off_t offset = 0,
		LPSECURITY_ATTRIBUTES sa = 0);

	Hazel_Mem_MAP (const tchar *filename,
		int len = -1,
		int prot = PROT_RDWR,
		int share = Hazel_MAP_PRIVATE,
		void *addr = 0,
		off_t offset = 0,
		LPSECURITY_ATTRIBUTES sa = 0);

	int map (Hazel_HANDLE handle,
		int length = -1,
		int prot = PROT_RDWR,
		int share = Hazel_MAP_PRIVATE,
		void *addr = 0,
		off_t offset = 0,
		LPSECURITY_ATTRIBUTES sa = 0);

	int map (int length ,
		int prot = PROT_RDWR,
		int share = Hazel_MAP_PRIVATE,
		void *addr = 0,
		off_t offset = 0,
		LPSECURITY_ATTRIBUTES sa = 0);


	int map (const tchar *filename,
		int len = -1,
		int prot = PROT_RDWR,
		int share = Hazel_MAP_PRIVATE,
		void *addr = 0,
		off_t offset = 0,
		LPSECURITY_ATTRIBUTES sa = 0);

	~Hazel_Mem_MAP (void);

	int close (void);
	int close_handle (void);
	int close_filemapping_handle (void);

	void *addr (void) const;
	size_t size (void) const;
	int unmap ( );
	int sync ( int flags = MS_SYNC);
	int protect ( int prot = PROT_RDWR);
	int remove (void);
	int advise (int behavior );

	const tstring& filename (void) const;
private:

	void *base_addr_;

	tstring filename_;

	size_t length_;

	Hazel_HANDLE handle_;

	Hazel_HANDLE file_mapping_;

	int map_it (Hazel_HANDLE handle,
		int len ,
		int prot = PROT_RDWR,
		int share = MAP_SHARED,
		void *addr = 0,
		off_t offset = 0,
		LPSECURITY_ATTRIBUTES sa = 0);
};

_networks_end

#endif // MMAP_H