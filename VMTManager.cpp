/*
// FILENAME: VMTManager.cpp
// DESC: Provides functions for managing
	VMT tables, hooking, storing backups,
	and restoring the tables when done,
	all in an anti-cheat safe way.
*/

//   --  Includes --  //
#include "stdafx.h"

// Top secret meme used for checking if a table is already memed up
#define VMTSIGNATURE 35492835

// Sets up the class and replaces the instance vtable pointer
// with a pointer to our custom vtable
// Takes a pointer to a class casted as a DWORD*

bool	VMTManager::Initialise(DWORD* InstancePointer)
{
	Instance = InstancePointer;
	OriginalTable = (DWORD*)*InstancePointer;
	int VMTSize = MethodCount(InstancePointer);
	size_t TableBytes = VMTSize*4;

	if(OriginalTable[VMTSize+1] == VMTSIGNATURE) return false; //Already managed by a VMTManager

	CustomTable = (DWORD*)malloc(TableBytes+8);
	if(!CustomTable) return false;
	memcpy( (void*)CustomTable, (void*)OriginalTable, VMTSize*4);

	CustomTable[VMTSize+1] = (DWORD)VMTSIGNATURE;

	*InstancePointer = (DWORD)CustomTable;

	initComplete = true;
	return true;
}

// Counts the amount of entries in a VMT table
// Takes a pointer to a class casted as a DWORD*
int		VMTManager::MethodCount(DWORD* InstancePointer)
{
	DWORD *VMT = (DWORD*)*InstancePointer;
	int Index = 0;
	int Amount = 0;
	while( !IsBadCodePtr((FARPROC)VMT[Index]) )
	{
		if(!IsBadCodePtr((FARPROC)VMT[Index]))
		{
			Amount++;
			Index++;
		}
	}

	return Amount;
}

// Hooks the method at the provided index
// Simply replaces the table entry with the new one
DWORD	VMTManager::HookMethod(DWORD NewFunction, int Index)
{
	if(initComplete)
	{
		CustomTable[Index] = NewFunction;
		return OriginalTable[Index];
	}
	else
		return NULL;
}

// Restores the original method pointer at the given index
void	VMTManager::UnhookMethod(int Index)
{
	if(initComplete)
		CustomTable[Index] = OriginalTable[Index];
	return;
}

// Restores the original pointer in the instance
void	VMTManager::RestoreOriginal()
{
	if(initComplete)
	{
		*Instance = (DWORD)OriginalTable;
	}
	return;
}

// Restores our custom pointer in the instance incase it has
//  been removed
void	VMTManager::RestoreCustom()
{
	if(initComplete)
	{
		*Instance = (DWORD)CustomTable;
	}
	return;
}

DWORD	VMTManager::GetOriginalFunction(int Index)
{
	return OriginalTable[Index];
}
