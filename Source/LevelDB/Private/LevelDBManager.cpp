// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDBManager.h"

#include "LevelDBContext.h"


ULevelDBContext* ULevelDBManager::GetDB(const FString& Name)
{
	if (LevelDBContexts.Contains(Name))
	{
		return LevelDBContexts[Name];
	}
	
	auto Context = NewObject<ULevelDBContext>(this); 
	if (Context && Context->OpenDatabase(Name))
	{
		LevelDBContexts.Add(Name, Context);
		return Context;
	}
	
	UE_LOG(LogTemp, Error, TEXT("Failed to open LevelDB database: %s"), *Name);
	return nullptr;
}

void ULevelDBManager::Close(const FString& Name)
{
	if (LevelDBContexts.Contains(Name))
	{
		if (auto Context = LevelDBContexts[Name])
		{
			Context->Close();
			LevelDBContexts.Remove(Name);
			return;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("No LevelDB opened with name: %s"), *Name);
}

void ULevelDBManager::CloseAll()
{
	for (auto& Context : LevelDBContexts)
	{
		if (Context.Value)
			Context.Value->Close();
	}
	LevelDBContexts.Empty();
}

void ULevelDBManager::Deinitialize()
{
	CloseAll();
	Super::Deinitialize();
}

