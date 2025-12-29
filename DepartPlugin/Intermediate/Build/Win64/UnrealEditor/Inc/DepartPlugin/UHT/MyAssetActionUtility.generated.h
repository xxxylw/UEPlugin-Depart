// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MyAssetActionUtility.h"

#ifdef DEPARTPLUGIN_MyAssetActionUtility_generated_h
#error "MyAssetActionUtility.generated.h already included, missing '#pragma once' in MyAssetActionUtility.h"
#endif
#define DEPARTPLUGIN_MyAssetActionUtility_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UMyAssetActionUtility ****************************************************
#define FID__materials__UEProjects_Depart_Depart_Plugins_DepartPlugin_Source_DepartPlugin_Public_MyAssetActionUtility_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execAddPrefix); \
	DECLARE_FUNCTION(execText);


DEPARTPLUGIN_API UClass* Z_Construct_UClass_UMyAssetActionUtility_NoRegister();

#define FID__materials__UEProjects_Depart_Depart_Plugins_DepartPlugin_Source_DepartPlugin_Public_MyAssetActionUtility_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMyAssetActionUtility(); \
	friend struct Z_Construct_UClass_UMyAssetActionUtility_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend DEPARTPLUGIN_API UClass* Z_Construct_UClass_UMyAssetActionUtility_NoRegister(); \
public: \
	DECLARE_CLASS2(UMyAssetActionUtility, UAssetActionUtility, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DepartPlugin"), Z_Construct_UClass_UMyAssetActionUtility_NoRegister) \
	DECLARE_SERIALIZER(UMyAssetActionUtility)


#define FID__materials__UEProjects_Depart_Depart_Plugins_DepartPlugin_Source_DepartPlugin_Public_MyAssetActionUtility_h_19_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMyAssetActionUtility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UMyAssetActionUtility(UMyAssetActionUtility&&) = delete; \
	UMyAssetActionUtility(const UMyAssetActionUtility&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMyAssetActionUtility); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMyAssetActionUtility); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMyAssetActionUtility) \
	NO_API virtual ~UMyAssetActionUtility();


#define FID__materials__UEProjects_Depart_Depart_Plugins_DepartPlugin_Source_DepartPlugin_Public_MyAssetActionUtility_h_16_PROLOG
#define FID__materials__UEProjects_Depart_Depart_Plugins_DepartPlugin_Source_DepartPlugin_Public_MyAssetActionUtility_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID__materials__UEProjects_Depart_Depart_Plugins_DepartPlugin_Source_DepartPlugin_Public_MyAssetActionUtility_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID__materials__UEProjects_Depart_Depart_Plugins_DepartPlugin_Source_DepartPlugin_Public_MyAssetActionUtility_h_19_INCLASS_NO_PURE_DECLS \
	FID__materials__UEProjects_Depart_Depart_Plugins_DepartPlugin_Source_DepartPlugin_Public_MyAssetActionUtility_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UMyAssetActionUtility;

// ********** End Class UMyAssetActionUtility ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID__materials__UEProjects_Depart_Depart_Plugins_DepartPlugin_Source_DepartPlugin_Public_MyAssetActionUtility_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
