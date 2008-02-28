// List_Tester.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <windows.h>
#include <malloc.h>

// Structure to be used for a list item. Typically, the first member 
// is of type SLIST_ENTRY. Additional members are used for data. 
// Here, the data is simply a signature for testing purposes. 

typedef struct _PROGRAM_ITEM {
    SLIST_ENTRY ItemEntry;
    ULONG Signature; 
} PROGRAM_ITEM, *PPROGRAM_ITEM;

void main( )
{
    ULONG Count;
    PSLIST_ENTRY FirstEntry, ListEntry;
    SLIST_HEADER ListHead;
    PPROGRAM_ITEM ProgramItem;

    // Initialize the list header.
    InitializeSListHead(&ListHead);

    // Insert 10 items into the list.
    for( Count = 1; Count <= 10; Count += 1 )
    {
        ProgramItem = (PPROGRAM_ITEM)malloc(sizeof(*ProgramItem));
        ProgramItem->Signature = Count;
        FirstEntry = InterlockedPushEntrySList(&ListHead, 
                       &ProgramItem->ItemEntry); 
    }

    // Remove 10 items from the list.
    for( Count = 10; Count >= 1; Count -= 1 )
    {
        ListEntry = InterlockedPopEntrySList(&ListHead);
        free(ListEntry);
    }

    // Flush the list and verify that the items are gone.
    ListEntry = InterlockedFlushSList(&ListHead);
    FirstEntry = InterlockedPopEntrySList(&ListHead);
    if (FirstEntry != NULL)
    {
        printf("Error: List is not empty.");
    }
}

