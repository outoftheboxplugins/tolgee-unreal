// Copyright (c) Tolgee. All Rights Reserved.

#pragma once

#include "Interfaces/IHttpRequest.h"
#include "Subsystems/EngineSubsystem.h"

#include "TolgeeLocalizationSubsystem.generated.h"

class FTolgeeTextSource;

USTRUCT()
struct FTolgeeLanguage
{
	GENERATED_BODY()

	UPROPERTY()
	int64 Id;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString Tag;

	UPROPERTY()
	FString OriginalName;

	UPROPERTY()
	FString FlagEmoji;

	UPROPERTY()
	bool Base;
};

USTRUCT()
struct FTolgeeTranslationLanguage
{
	GENERATED_BODY()

	UPROPERTY()
	int64 Id;

	UPROPERTY()
	FString Text;
};

USTRUCT()
struct FTolgeeTranslation
{
	GENERATED_BODY()

	UPROPERTY()
	FTolgeeTranslationLanguage En;

	UPROPERTY()
	FTolgeeTranslationLanguage De;
};

USTRUCT()
struct FTolgeeKey
{
	GENERATED_BODY()

	UPROPERTY()
	int64 KeyId;

	UPROPERTY()
	FString KeyName;

	UPROPERTY()
	int64 KeyNamespaceId;

	UPROPERTY()
	FString KeyNamespace;

	UPROPERTY()
	FTolgeeTranslation Translations;
};

USTRUCT()
struct FTolgeeEmbededData
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FTolgeeKey> Keys;
};

USTRUCT()
struct FTolgeeTranslationData
{
	GENERATED_BODY()

	UPROPERTY()
	FString NextCursor;

	UPROPERTY()
	TArray<FTolgeeLanguage> SelectedLanguages;

	UPROPERTY()
	FTolgeeEmbededData _Embedded;
};

/**
 *
 */
UCLASS()
class TOLGEE_API UTolgeeLocalizationSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void FetchTranslation();
	void OnTranslationFetched(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	TSharedPtr<FTolgeeTextSource> TextSource;
};
