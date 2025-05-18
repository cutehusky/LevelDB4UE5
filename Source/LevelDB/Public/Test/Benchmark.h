// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Benchmark.generated.h"

class UTestObject;
class ULevelDBContext;
class UTestSaveGame;
/**
 * 
 */
UCLASS()
class LEVELDB_API UBenchmark : public UObject
{
	GENERATED_BODY()
public:
	static void BenchmarkLevelDB(ULevelDBContext* LevelDB, UTestObject* ObjectToSave, int Iterations);
	static void BenchmarkSaveGame(UTestSaveGame* ObjectToSave, int Iterations);
};
