// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TestObject.generated.h"

/**
 * 
 */
UCLASS()
class LEVELDB_API UTestObject : public UObject
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

	static UTestObject* CreateTestObject(UObject* Outer);
	static bool AreTestObjectsEqual(const UTestObject* A, const UTestObject* B);
};
