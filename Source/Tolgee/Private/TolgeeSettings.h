// Copyright (c) Tolgee. All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettings.h"

#include "TolgeeSettings.generated.h"

/**
 *
 */
UCLASS(Config = Tolgee)
class UTolgeeSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "Tolgee Localization")
	FString ApiKey = TEXT("tgpak_ge4dimc7mm2xenlbmz3gmzlrovrxandqofzwgmlhnrtgszdnmm");

	UPROPERTY(Config, EditAnywhere, Category = "Tolgee Localization")
	FString Project;

	UPROPERTY(Config, EditAnywhere, Category = "Tolgee Localization")
	float UpdateInterval = 60.0f;
};
