// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyAssetActionUtility.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeMyAssetActionUtility() {}

// ********** Begin Cross Module References ********************************************************
BLUTILITY_API UClass* Z_Construct_UClass_UAssetActionUtility();
DEPARTPLUGIN_API UClass* Z_Construct_UClass_UMyAssetActionUtility();
DEPARTPLUGIN_API UClass* Z_Construct_UClass_UMyAssetActionUtility_NoRegister();
UPackage* Z_Construct_UPackage__Script_DepartPlugin();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UMyAssetActionUtility Function AddPrefix *********************************
struct Z_Construct_UFunction_UMyAssetActionUtility_AddPrefix_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "ModuleRelativePath", "Public/MyAssetActionUtility.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMyAssetActionUtility_AddPrefix_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMyAssetActionUtility, nullptr, "AddPrefix", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyAssetActionUtility_AddPrefix_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMyAssetActionUtility_AddPrefix_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UMyAssetActionUtility_AddPrefix()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMyAssetActionUtility_AddPrefix_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMyAssetActionUtility::execAddPrefix)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AddPrefix();
	P_NATIVE_END;
}
// ********** End Class UMyAssetActionUtility Function AddPrefix ***********************************

// ********** Begin Class UMyAssetActionUtility Function Text **************************************
struct Z_Construct_UFunction_UMyAssetActionUtility_Text_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "ModuleRelativePath", "Public/MyAssetActionUtility.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMyAssetActionUtility_Text_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMyAssetActionUtility, nullptr, "Text", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyAssetActionUtility_Text_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMyAssetActionUtility_Text_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UMyAssetActionUtility_Text()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMyAssetActionUtility_Text_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMyAssetActionUtility::execText)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Text();
	P_NATIVE_END;
}
// ********** End Class UMyAssetActionUtility Function Text ****************************************

// ********** Begin Class UMyAssetActionUtility ****************************************************
void UMyAssetActionUtility::StaticRegisterNativesUMyAssetActionUtility()
{
	UClass* Class = UMyAssetActionUtility::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "AddPrefix", &UMyAssetActionUtility::execAddPrefix },
		{ "Text", &UMyAssetActionUtility::execText },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UMyAssetActionUtility;
UClass* UMyAssetActionUtility::GetPrivateStaticClass()
{
	using TClass = UMyAssetActionUtility;
	if (!Z_Registration_Info_UClass_UMyAssetActionUtility.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("MyAssetActionUtility"),
			Z_Registration_Info_UClass_UMyAssetActionUtility.InnerSingleton,
			StaticRegisterNativesUMyAssetActionUtility,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UMyAssetActionUtility.InnerSingleton;
}
UClass* Z_Construct_UClass_UMyAssetActionUtility_NoRegister()
{
	return UMyAssetActionUtility::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UMyAssetActionUtility_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "MyAssetActionUtility.h" },
		{ "ModuleRelativePath", "Public/MyAssetActionUtility.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UMyAssetActionUtility_AddPrefix, "AddPrefix" }, // 2957292247
		{ &Z_Construct_UFunction_UMyAssetActionUtility_Text, "Text" }, // 250029413
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMyAssetActionUtility>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UMyAssetActionUtility_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAssetActionUtility,
	(UObject* (*)())Z_Construct_UPackage__Script_DepartPlugin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMyAssetActionUtility_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMyAssetActionUtility_Statics::ClassParams = {
	&UMyAssetActionUtility::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMyAssetActionUtility_Statics::Class_MetaDataParams), Z_Construct_UClass_UMyAssetActionUtility_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UMyAssetActionUtility()
{
	if (!Z_Registration_Info_UClass_UMyAssetActionUtility.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMyAssetActionUtility.OuterSingleton, Z_Construct_UClass_UMyAssetActionUtility_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMyAssetActionUtility.OuterSingleton;
}
UMyAssetActionUtility::UMyAssetActionUtility(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UMyAssetActionUtility);
UMyAssetActionUtility::~UMyAssetActionUtility() {}
// ********** End Class UMyAssetActionUtility ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID__materials__UEProjects_Depart_Depart_Plugins_DepartPlugin_Source_DepartPlugin_Public_MyAssetActionUtility_h__Script_DepartPlugin_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMyAssetActionUtility, UMyAssetActionUtility::StaticClass, TEXT("UMyAssetActionUtility"), &Z_Registration_Info_UClass_UMyAssetActionUtility, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMyAssetActionUtility), 671758962U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID__materials__UEProjects_Depart_Depart_Plugins_DepartPlugin_Source_DepartPlugin_Public_MyAssetActionUtility_h__Script_DepartPlugin_878159534(TEXT("/Script/DepartPlugin"),
	Z_CompiledInDeferFile_FID__materials__UEProjects_Depart_Depart_Plugins_DepartPlugin_Source_DepartPlugin_Public_MyAssetActionUtility_h__Script_DepartPlugin_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID__materials__UEProjects_Depart_Depart_Plugins_DepartPlugin_Source_DepartPlugin_Public_MyAssetActionUtility_h__Script_DepartPlugin_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
