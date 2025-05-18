// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TestObject.h"

UTestObject* UTestObject::CreateTestObject(UObject* Outer)
{
	UTestObject* SaveData = NewObject<UTestObject>(Outer);
	
	SaveData->Name = TEXT("BenchmarkObject");
	SaveData->Score = 9001;

	for (int i = 0; i < 100; ++i)
	{
		SaveData->FloatValues.Add(FMath::FRand());
		SaveData->StringIntMap.Add(FString::Printf(TEXT("Key_%d"), i), i);
	}

	SaveData->bIsActive = true;
	SaveData->Location = FVector(100.0f, 200.0f, 300.0f);
	SaveData->Rotation = FRotator(45.0f, 90.0f, 180.0f);
	SaveData->StringArray = { TEXT("Alpha"), TEXT("Bravo"), TEXT("Charlie") };
	SaveData->IntStringMap.Add(1, TEXT("One"));
	SaveData->IntStringMap.Add(2, TEXT("Two"));
	SaveData->IntStringMap.Add(3, TEXT("Three"));
	SaveData->DoubleValue = 3.14159265359;
	return SaveData;
}

bool UTestObject::AreTestObjectsEqual(const UTestObject* A, const UTestObject* B)
{
	if (!A || !B)
	{
		UE_LOG(LogTemp, Error, TEXT("One or both SaveGame objects are null."));
		return false;
	}

	if (A->Name != B->Name)
	{
		UE_LOG(LogTemp, Error, TEXT("Name mismatch: '%s' vs '%s'"), *A->Name, *B->Name);
		return false;
	}

	if (A->Score != B->Score)
	{
		UE_LOG(LogTemp, Error, TEXT("Score mismatch: %d vs %d"), A->Score, B->Score);
		return false;
	}

	if (A->FloatValues.Num() != B->FloatValues.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("FloatValues array size mismatch: %d vs %d"), A->FloatValues.Num(), B->FloatValues.Num());
		return false;
	}

	for (int32 i = 0; i < A->FloatValues.Num(); ++i)
	{
		if (!FMath::IsNearlyEqual(A->FloatValues[i], B->FloatValues[i]))
		{
			UE_LOG(LogTemp, Error, TEXT("FloatValues[%d] mismatch: %f vs %f"), i, A->FloatValues[i], B->FloatValues[i]);
			return false;
		}
	}

	if (A->StringIntMap.Num() != B->StringIntMap.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("StringIntMap size mismatch: %d vs %d"), A->StringIntMap.Num(), B->StringIntMap.Num());
		return false;
	}

	for (const auto& Pair : A->StringIntMap)
	{
		const int32* OtherValue = B->StringIntMap.Find(Pair.Key);
		if (!OtherValue)
		{
			UE_LOG(LogTemp, Error, TEXT("Key '%s' not found in B->StringIntMap"), *Pair.Key);
			return false;
		}

		if (*OtherValue != Pair.Value)
		{
			UE_LOG(LogTemp, Error, TEXT("Value mismatch for key '%s': %d vs %d"), *Pair.Key, Pair.Value, *OtherValue);
			return false;
		}
	}

	
	if (A->bIsActive != B->bIsActive)
	{
		UE_LOG(LogTemp, Error, TEXT("bIsActive mismatch: %s vs %s"), A->bIsActive ? TEXT("true") : TEXT("false"), B->bIsActive ? TEXT("true") : TEXT("false"));
		return false;
	}

	if (!A->Location.Equals(B->Location, KINDA_SMALL_NUMBER))
	{
		UE_LOG(LogTemp, Error, TEXT("Location mismatch: %s vs %s"), *A->Location.ToString(), *B->Location.ToString());
		return false;
	}

	if (!A->Rotation.Equals(B->Rotation, KINDA_SMALL_NUMBER))
	{
		UE_LOG(LogTemp, Error, TEXT("Rotation mismatch: %s vs %s"), *A->Rotation.ToString(), *B->Rotation.ToString());
		return false;
	}

	if (A->StringArray.Num() != B->StringArray.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("StringArray size mismatch: %d vs %d"), A->StringArray.Num(), B->StringArray.Num());
		return false;
	}
	for (int32 i = 0; i < A->StringArray.Num(); ++i)
	{
		if (A->StringArray[i] != B->StringArray[i])
		{
			UE_LOG(LogTemp, Error, TEXT("StringArray[%d] mismatch: '%s' vs '%s'"), i, *A->StringArray[i], *B->StringArray[i]);
			return false;
		}
	}

	if (A->IntStringMap.Num() != B->IntStringMap.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("IntStringMap size mismatch: %d vs %d"), A->IntStringMap.Num(), B->IntStringMap.Num());
		return false;
	}
	for (const auto& Pair : A->IntStringMap)
	{
		const FString* OtherValue = B->IntStringMap.Find(Pair.Key);
		if (!OtherValue)
		{
			UE_LOG(LogTemp, Error, TEXT("Key '%d' not found in B->IntStringMap"), Pair.Key);
			return false;
		}
		if (*OtherValue != Pair.Value)
		{
			UE_LOG(LogTemp, Error, TEXT("IntStringMap value mismatch for key '%d': '%s' vs '%s'"), Pair.Key, *Pair.Value, **OtherValue);
			return false;
		}
	}

	if (!FMath::IsNearlyEqual(A->DoubleValue, B->DoubleValue, KINDA_SMALL_NUMBER))
	{
		UE_LOG(LogTemp, Error, TEXT("DoubleValue mismatch: %f vs %f"), A->DoubleValue, B->DoubleValue);
		return false;
	}
	return true;
}
