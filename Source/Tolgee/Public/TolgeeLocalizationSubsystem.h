// Copyright (c) Tolgee. All Rights Reserved.

#pragma once

#include "Interfaces/IHttpRequest.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "TolgeeLocalizationSubsystem.generated.h"

class FTolgeeTextSource;

USTRUCT()
struct FTolgeeTranslation
{
	GENERATED_BODY()

	UPROPERTY()
	int64 Id;

	UPROPERTY()
	FString Text;
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
};

/**
 *
 */
UCLASS()
class TOLGEE_API UTolgeeLocalizationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	void ManualFetch();

private:
	void GetLocalizedResources(
		const ELocalizationLoadFlags InLoadFlags, TArrayView<const FString> InPrioritizedCultures, FTextLocalizationResource& InOutNativeResource, FTextLocalizationResource& InOutLocalizedResource
	) const;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void FetchTranslation();
	void OnTranslationFetched(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnTranslationReady();

	// TODO: Temp work delete after better testing is implemented.
	void TestPrint();

	FTimerHandle AutoFetchTimerHandle;

	TSharedPtr<FTolgeeTextSource> TextSource;

	TArray<TSharedPtr<FJsonValue>> TranslatedKeys;
};
