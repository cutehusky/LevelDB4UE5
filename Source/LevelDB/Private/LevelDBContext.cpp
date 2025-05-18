// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDBContext.h"

bool ULevelDBContext::OpenDatabase(const FString& Name, bool bCreateIfMissing)
{
	leveldb::Options Options;
	Options.create_if_missing = bCreateIfMissing;

	const FString RelativePath = FPaths::ProjectSavedDir() / Name;
	const FString AbsolutePath = FPlatformFileManager::Get().GetPlatformFile().ConvertToAbsolutePathForExternalAppForWrite(*RelativePath);
	UE_LOG(LogTemp, Log, TEXT("LevelDB Path: %s"), *AbsolutePath);
	leveldb::Status Status = leveldb::DB::Open(Options,
		TCHAR_TO_UTF8(*AbsolutePath), &db);
	return Status.ok();
}

bool ULevelDBContext::PutString(const FString& Key, const FString& Value)
{
	if (db == nullptr)
		return false;
	std::string KeyStr(TCHAR_TO_UTF8(*Key));
	std::string ValueStr(TCHAR_TO_UTF8(*Value));
	leveldb::Status status = db->Put(leveldb::WriteOptions(), KeyStr, ValueStr);
	return status.ok();
}

bool ULevelDBContext::GetString(const FString& Key, FString& OutValue)
{
	if (db == nullptr)
		return false;
	std::string StdKey = TCHAR_TO_UTF8(*Key);
	std::string Result;
	leveldb::ReadOptions ReadOptions;
	leveldb::Status Status = db->Get(ReadOptions, StdKey, &Result);
	if (Status.ok())
	{
		OutValue = UTF8_TO_TCHAR(Result.c_str());
		return true;
	}
	return false;
}

bool ULevelDBContext::PutBytes(const FString& Key, const TArray<uint8>& Data)
{
	if (!db)
		return false;
	leveldb::WriteOptions WriteOptions;
	std::string StdKey = TCHAR_TO_UTF8(*Key);
	leveldb::Slice ValueSlice(reinterpret_cast<const char*>(Data.GetData()), Data.Num());
	leveldb::Status Status = db->Put(WriteOptions, StdKey, ValueSlice);
	return Status.ok();
}

bool ULevelDBContext::GetBytes(const FString& Key, TArray<uint8>& OutData)
{
	if (db == nullptr)
		return false;
	std::string StdKey = TCHAR_TO_UTF8(*Key);
	std::string Result;
	leveldb::ReadOptions ReadOptions;
	leveldb::Status Status = db->Get(ReadOptions, StdKey, &Result);
	if (Status.ok())
	{
		OutData.SetNumUninitialized(Result.size());
		FMemory::Memcpy(OutData.GetData(), Result.data(), Result.size());
		return true;
	}
	return false;
}

bool ULevelDBContext::PutRaw(const TArray<uint8>& Key, const TArray<uint8>& Value)
{
	if (db != nullptr)
		return false;

	leveldb::WriteOptions WriteOptions;

	leveldb::Slice KeySlice(reinterpret_cast<const char*>(Key.GetData()), Key.Num());
	leveldb::Slice ValueSlice(reinterpret_cast<const char*>(Value.GetData()), Value.Num());

	leveldb::Status Status = db->Put(WriteOptions, KeySlice, ValueSlice);
	return Status.ok();
}

bool ULevelDBContext::GetRaw(const TArray<uint8>& Key, TArray<uint8>& OutValue)
{
	if (!db)
		return false;
	leveldb::ReadOptions ReadOptions;
	leveldb::Slice KeySlice(reinterpret_cast<const char*>(Key.GetData()), Key.Num());
	std::string Result;
	leveldb::Status Status = db->Get(ReadOptions, KeySlice, &Result);
	if (Status.ok())
	{
		OutValue.SetNumUninitialized(Result.size());
		FMemory::Memcpy(OutValue.GetData(), Result.data(), Result.size());
		return true;
	}
	return false;
}

UObject* ULevelDBContext::GetObjectByClass(const FString& Key, TSubclassOf<UObject> ObjectClass)
{
	if (!db || !*ObjectClass)
		return nullptr;
	UObject* newObj = NewObject<UObject>(GetTransientPackage(), *ObjectClass);
	if (!LoadUObject(Key, newObj))
		return nullptr;
	return newObj;
}

void ULevelDBContext::Close()
{
	if (db != nullptr)
	{
		delete db;
		db = nullptr;
	}
}

bool ULevelDBContext::IsOpened()
{
	return db != nullptr;
}

void ULevelDBContext::BeginDestroy()
{
	Close();
	UObject::BeginDestroy();
}

bool ULevelDBContext::SaveUObject(const FString& Key, UObject* Object)
{
	if (!db || !Object)
		return false;

	TArray<uint8> Buffer;
	FMemoryWriter Writer(Buffer, true);
	
	Object->Serialize(Writer);

	std::string StdKey = TCHAR_TO_UTF8(*Key);
	leveldb::Slice Value(reinterpret_cast<const char*>(Buffer.GetData()), Buffer.Num());
	return db->Put(leveldb::WriteOptions(), StdKey, Value).ok();
}

bool ULevelDBContext::LoadUObject(const FString& Key, UObject* Object)
{
	if (!db || !Object)
		return false;

	std::string StdKey = TCHAR_TO_UTF8(*Key);
	std::string RawData;
	leveldb::Status Status = db->Get(leveldb::ReadOptions(), StdKey, &RawData);
	if (!Status.ok())
		return false;

	TArray<uint8> Buffer;
	Buffer.Append(reinterpret_cast<const uint8*>(RawData.data()), RawData.size());

	FMemoryReader Reader(Buffer, true);
	Object->Serialize(Reader);
	return true;
}

