// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "leveldb/db.h"
#include "UObject/Object.h"
#include "LevelDBContext.generated.h"

/**
 * 
 */
UCLASS()
class LEVELDB_API ULevelDBContext : public UObject
{
	GENERATED_BODY()
	leveldb::DB* db = nullptr;
public:
	UFUNCTION(BlueprintCallable, Category = "LevelDB")
	bool OpenDatabase(const FString& Name, bool bCreateIfMissing = true);

	UFUNCTION(BlueprintCallable, Category = "LevelDB")
	bool PutString(const FString& Key, const FString& Value);

	UFUNCTION(BlueprintCallable, Category = "LevelDB")
	bool GetString(const FString& Key, FString& OutValue);

	UFUNCTION(BlueprintCallable, Category = "LevelDB")
	bool PutBytes(const FString& Key, const TArray<uint8>& Data);

	UFUNCTION(BlueprintCallable, Category = "LevelDB")
	bool GetBytes(const FString& Key, TArray<uint8>& OutData);

	UFUNCTION(BlueprintCallable, Category = "LevelDB")
	bool PutRaw(const TArray<uint8>& Key, const TArray<uint8>& Value);

	UFUNCTION(BlueprintCallable, Category = "LevelDB")
	bool GetRaw(const TArray<uint8>& Key, TArray<uint8>& OutValue);

	UFUNCTION(BlueprintCallable, Category = "LevelDB")
	bool SaveUObject(const FString& Key, UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "LevelDB")
	bool LoadUObject(const FString& Key, UObject* Object);
	
	template<typename T>
	T* GetObject(const FString& Key) 
	{
		if (db == nullptr)
			return nullptr;
		auto newObj = NewObject<T>();
		if (!LoadUObject(Key, newObj))
			return nullptr;
		return newObj;
	}

	UFUNCTION(BlueprintCallable, Category = "LevelDB")
	UObject* GetObjectByClass(const FString& Key, TSubclassOf<UObject> ObjectClass);

	UFUNCTION(BlueprintCallable, Category = "LevelDB")
	void Close();
	
	UFUNCTION(BlueprintCallable, Category = "LevelDB")
	bool IsOpened();

	virtual void BeginDestroy() override;
};