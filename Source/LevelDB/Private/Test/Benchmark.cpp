// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/Benchmark.h"

#include "LevelDBContext.h"
#include "Kismet/GameplayStatics.h"
#include "Test/TestObject.h"
#include "Test/TestSaveGame.h"

void UBenchmark::BenchmarkLevelDB(ULevelDBContext* LevelDB, UTestObject* ObjectToSave, int Iterations = 100)
{

	// --- WRITE Benchmark ---
	double StartTime = FPlatformTime::Seconds();
	for (int i = 0; i < Iterations; ++i)
	{
		LevelDB->SaveUObject(FString::Printf(TEXT("Benchmark_%d"), i), ObjectToSave);
	}
	double EndTime = FPlatformTime::Seconds();
	
	UE_LOG(LogTemp, Log, TEXT("LevelDB WRITE (%d iterations): %.6f sec"), Iterations, EndTime - StartTime);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("LevelDB WRITE (%d iterations): %.6f sec"), Iterations, EndTime - StartTime));

	// --- READ Benchmark ---
	StartTime = FPlatformTime::Seconds();
	for (int i = 0; i < Iterations; ++i)
	{
		UTestObject* TempObject = LevelDB->GetObject<UTestObject>(FString::Printf(TEXT("Benchmark_%d"), i));
		UTestObject::AreTestObjectsEqual(TempObject, ObjectToSave);
	}
	EndTime = FPlatformTime::Seconds();
	
	UE_LOG(LogTemp, Log, TEXT("LevelDB READ (%d iterations): %.6f sec"), Iterations, EndTime - StartTime);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("LevelDB READ (%d iterations): %.6f sec"), Iterations, EndTime - StartTime));
}

void UBenchmark::BenchmarkSaveGame(UTestSaveGame* ObjectToSave, int Iterations = 100)
{
	// --- WRITE Benchmark ---
	double StartTime = FPlatformTime::Seconds();
	for (int i = 0; i < Iterations; ++i)
	{
		UGameplayStatics::SaveGameToSlot(ObjectToSave, FString::Printf(TEXT("Benchmark_%d"), i), 0);
	}
	double EndTime = FPlatformTime::Seconds();

	UE_LOG(LogTemp, Log, TEXT("SaveGame WRITE (%d iterations): %.6f sec"), Iterations, EndTime - StartTime);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("SaveGame WRITE (%d iterations): %.6f sec"), Iterations, EndTime - StartTime));

	// --- READ Benchmark ---
	StartTime = FPlatformTime::Seconds();
	for (int i = 0; i < Iterations; ++i)
	{
		USaveGame* Loaded = UGameplayStatics::LoadGameFromSlot(FString::Printf(TEXT("Benchmark_%d"), i), 0);
		UTestSaveGame* res = Cast<UTestSaveGame>(Loaded);
		UTestSaveGame::AreSaveGamesEqual(res, ObjectToSave);
	}
	EndTime = FPlatformTime::Seconds();

	UE_LOG(LogTemp, Log, TEXT("SaveGame READ (%d iterations): %.6f sec"), Iterations, EndTime - StartTime);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("SaveGame READ (%d iterations): %.6f sec"), Iterations, EndTime - StartTime));
}