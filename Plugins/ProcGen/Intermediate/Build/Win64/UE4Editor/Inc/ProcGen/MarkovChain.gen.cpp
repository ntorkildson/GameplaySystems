// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProcGen/Public/MarkovChain.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMarkovChain() {}
// Cross Module References
	PROCGEN_API UClass* Z_Construct_UClass_AMarkovChain_NoRegister();
	PROCGEN_API UClass* Z_Construct_UClass_AMarkovChain();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_ProcGen();
// End Cross Module References
	void AMarkovChain::StaticRegisterNativesAMarkovChain()
	{
	}
	UClass* Z_Construct_UClass_AMarkovChain_NoRegister()
	{
		return AMarkovChain::StaticClass();
	}
	struct Z_Construct_UClass_AMarkovChain_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMarkovChain_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ProcGen,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMarkovChain_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "MarkovChain.h" },
		{ "ModuleRelativePath", "Public/MarkovChain.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMarkovChain_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMarkovChain>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AMarkovChain_Statics::ClassParams = {
		&AMarkovChain::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AMarkovChain_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AMarkovChain_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AMarkovChain()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AMarkovChain_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AMarkovChain, 584836648);
	template<> PROCGEN_API UClass* StaticClass<AMarkovChain>()
	{
		return AMarkovChain::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AMarkovChain(Z_Construct_UClass_AMarkovChain, &AMarkovChain::StaticClass, TEXT("/Script/ProcGen"), TEXT("AMarkovChain"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMarkovChain);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
