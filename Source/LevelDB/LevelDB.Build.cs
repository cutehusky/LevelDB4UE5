// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class LevelDB : ModuleRules
{
	public LevelDB(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PublicDefinitions.Add("HAVE_FULLFSYNC=0");
			PublicDefinitions.Add("HAVE_FDATASYNC=0");
		}
		
		PublicDefinitions.Add("HAVE_SNAPPY=0");
		PublicDefinitions.Add("HAVE_ZSTD=0");
		PublicDefinitions.Add("HAVE_CRC32C=0");

		var LevelDbPath = Path.Combine(ModuleDirectory,"ThirdParty", "leveldb");
		PublicIncludePaths.Add(LevelDbPath);
		PublicIncludePaths.Add(Path.Combine(LevelDbPath, "include"));
		PublicIncludePaths.Add(Path.Combine(LevelDbPath, "db"));
		PublicIncludePaths.Add(Path.Combine(LevelDbPath, "util"));
		PublicIncludePaths.Add(Path.Combine(LevelDbPath, "helpers"));
		PublicIncludePaths.Add(Path.Combine(LevelDbPath, "table"));
		PublicIncludePaths.Add(Path.Combine(LevelDbPath, "port"));
		
		PublicDependencyModuleNames.AddRange(["Core"]);
		PrivateDependencyModuleNames.AddRange(["CoreUObject", "Engine" ]);
		
		// DynamicallyLoadedModuleNames.AddRange([]);
	}
}
