// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProcGen/Public/GridHelper.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGridHelper() {}
// Cross Module References
	PROCGEN_API UClass* Z_Construct_UClass_UGridHelper_NoRegister();
	PROCGEN_API UClass* Z_Construct_UClass_UGridHelper();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_ProcGen();
// End Cross Module References
	DEFINE_FUNCTION(UGridHelper::execGenerateGrid)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GenerateGrid();
		P_NATIVE_END;
	}
	void UGridHelper::StaticRegisterNativesUGridHelper()
	{
		UClass* Class = UGridHelper::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GenerateGrid", &UGridHelper::execGenerateGrid },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGridHelper_GenerateGrid_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGridHelper_GenerateGrid_Statics::Function_MetaDataParams[] = {
		{ "Category", "ProcGenLibrary | GridHelper" },
		{ "ModuleRelativePath", "Public/GridHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGridHelper_GenerateGrid_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGridHelper, nullptr, "GenerateGrid", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGridHelper_GenerateGrid_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGridHelper_GenerateGrid_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGridHelper_GenerateGrid()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGridHelper_GenerateGrid_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UGridHelper_NoRegister()
	{
		return UGridHelper::StaticClass();
	}
	struct Z_Construct_UClass_UGridHelper_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGridHelper_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_ProcGen,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UGridHelper_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGridHelper_GenerateGrid, "GenerateGrid" }, // 3442164805
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGridHelper_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GridHelper.h" },
		{ "ModuleRelativePath", "Public/GridHelper.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGridHelper_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGridHelper>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UGridHelper_Statics::ClassParams = {
		&UGridHelper::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UGridHelper_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGridHelper_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGridHelper()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UGridHelper_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGridHelper, 3756734518);
	template<> PROCGEN_API UClass* StaticClass<UGridHelper>()
	{
		return UGridHelper::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGridHelper(Z_Construct_UClass_UGridHelper, &UGridHelper::StaticClass, TEXT("/Script/ProcGen"), TEXT("UGridHelper"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGridHelper);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
