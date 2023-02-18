// Copyright (c) Tolgee. All Rights Reserved.

#include "TolgeeTextSource.h"

#include "Internationalization/TextLocalizationResource.h"
bool FTolgeeTextSource::GetNativeCultureName(const ELocalizedTextSourceCategory InCategory, FString& OutNativeCultureName)
{
	return false;
}

void FTolgeeTextSource::GetLocalizedCultureNames(const ELocalizationLoadFlags InLoadFlags, TSet<FString>& OutLocalizedCultureNames)
{
}

void FTolgeeTextSource::LoadLocalizedResources(
	const ELocalizationLoadFlags InLoadFlags, TArrayView<const FString> InPrioritizedCultures, FTextLocalizationResource& InOutNativeResource, FTextLocalizationResource& InOutLocalizedResource
)
{
	GetLocalizedResources.Execute(InLoadFlags, InPrioritizedCultures, InOutNativeResource, InOutLocalizedResource);
}