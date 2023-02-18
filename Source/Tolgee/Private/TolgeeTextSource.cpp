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
	InOutLocalizedResource.AddEntry(TEXT("NamespaceTest"), TEXT("KeyTest"), TEXT("English Test"), TEXT("InLocalizedString"), 0);
	InOutLocalizedResource.AddEntry(TEXT("NamespaceTest"), TEXT("TimeFormat"), TEXT("{0}|plural(one=time, other=times)"), TEXT("{0}|plural(one=one, other=other)"), 0);
	/*auto GetLocalizedStringForPolyglotData = [&InPolyglotTextData](TArrayView<const FString> InCulturesToCheck, FString& OutLocalizedString, int32* OutLocalizedPriority = nullptr) -> bool
	{
		for (int32 CultureIndex = 0; CultureIndex < InCulturesToCheck.Num(); ++CultureIndex)
		{
			const FString& CultureName = InCulturesToCheck[CultureIndex];

			if (InPolyglotTextData.GetLocalizedString(CultureName, OutLocalizedString))
			{
				if (OutLocalizedPriority)
				{
					*OutLocalizedPriority = CultureIndex;
				}
				return true;
			}
		}

		if (OutLocalizedPriority)
		{
			*OutLocalizedPriority = 0;
		}
		OutLocalizedString = InPolyglotTextData.GetNativeString();
		return true;
	};

	const int32 BaseResourcePriority = GetPriority() * -1; // Flip the priority as larger text source priorities are more important, but smaller text resource priorities are more important
	const FString NativeCulture = InPolyglotTextData.ResolveNativeCulture();

	// We skip loading the native text if we're transitioning to the native culture as there's no extra work that needs to be done
	if (ShouldLoadNative(InLoadFlags) && !InPrioritizedCultures.Contains(NativeCulture))
	{
		FString LocalizedString;
		if (GetLocalizedStringForPolyglotData(TArrayView<const FString>(&NativeCulture, 1), LocalizedString))
		{
			InOutNativeResource.AddEntry(InPolyglotTextData.GetNamespace(), InPolyglotTextData.GetKey(), InPolyglotTextData.GetNativeString(), LocalizedString, BaseResourcePriority);
		}
	}

	if (InPolyglotTextData.GetCategory() == ELocalizedTextSourceCategory::Game && ShouldLoadNativeGameData(InLoadFlags))
	{
		// The editor cheats and loads the native language's localizations for game data.
		FString LocalizedString;
		if (GetLocalizedStringForPolyglotData(TArrayView<const FString>(&NativeCulture, 1), LocalizedString))
		{
			InOutLocalizedResource.AddEntry(InPolyglotTextData.GetNamespace(), InPolyglotTextData.GetKey(), InPolyglotTextData.GetNativeString(), LocalizedString, BaseResourcePriority);
		}
	}
	else
	{
		// Find culture localization resource.
		int32 LocalizedPriority = 0;
		FString LocalizedString;
		if (GetLocalizedStringForPolyglotData(InPrioritizedCultures, LocalizedString, &LocalizedPriority))
		{
			InOutLocalizedResource.AddEntry(
				InPolyglotTextData.GetNamespace(), InPolyglotTextData.GetKey(), InPolyglotTextData.GetNativeString(), LocalizedString, BaseResourcePriority + LocalizedPriority + 1
			);
		}
	}
	*/
}