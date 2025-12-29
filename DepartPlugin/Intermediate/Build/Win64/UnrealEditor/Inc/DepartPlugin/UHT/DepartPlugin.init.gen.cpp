// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDepartPlugin_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_DepartPlugin;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_DepartPlugin()
	{
		if (!Z_Registration_Info_UPackage__Script_DepartPlugin.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/DepartPlugin",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000040,
				0xD401B583,
				0xA6ED8160,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_DepartPlugin.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_DepartPlugin.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_DepartPlugin(Z_Construct_UPackage__Script_DepartPlugin, TEXT("/Script/DepartPlugin"), Z_Registration_Info_UPackage__Script_DepartPlugin, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xD401B583, 0xA6ED8160));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
