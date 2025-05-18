// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LevelDBManager.generated.h"

class ULevelDBContext;
/**
 * 
 */
UCLASS()
class LEVELDB_API ULevelDBManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TMap<FString, ULevelDBContext*> LevelDBContexts;
	
public:
	ULevelDBContext* GetDB(const FString& Name);
	void Close(const FString& Name);
	void CloseAll();

	virtual void Deinitialize() override;
};
