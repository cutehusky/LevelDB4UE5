// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TestSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class LEVELDB_API UTestSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Benchmark")
	FString Name;

	UPROPERTY(VisibleAnywhere, Category = "Benchmark")
	int32 Score;

	UPROPERTY(VisibleAnywhere, Category = "Benchmark")
	TArray<float> FloatValues;

	UPROPERTY(VisibleAnywhere, Category = "Benchmark")
	TMap<FString, int32> StringIntMap;

	UPROPERTY(VisibleAnywhere, Category = "Benchmark")
	bool bIsActive;

	UPROPERTY(VisibleAnywhere, Category = "Benchmark")
	FVector Location;

	UPROPERTY(VisibleAnywhere, Category = "Benchmark")
	FRotator Rotation;

	UPROPERTY(VisibleAnywhere, Category = "Benchmark")
	TArray<FString> StringArray;

	UPROPERTY(VisibleAnywhere, Category = "Benchmark")
	TMap<int32, FString> IntStringMap;

	UPROPERTY(VisibleAnywhere, Category = "Benchmark")
	double DoubleValue;
	
	static UTestSaveGame* CreateSaveGameData();
	static bool AreSaveGamesEqual(const UTestSaveGame* A, const UTestSaveGame* B);
};
