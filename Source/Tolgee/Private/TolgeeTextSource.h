// Copyright (c) Tolgee. All Rights Reserved.

#pragma once

#include "Internationalization/ILocalizedTextSource.h"

using FGetLocalizedResources = TDelegate<
	void(const ELocalizationLoadFlags InLoadFlags, TArrayView<const FString> InPrioritizedCultures, FTextLocalizationResource& InOutNativeResource, FTextLocalizationResource& InOutLocalizedResource)>;

/**
 *
 */
class FTolgeeTextSource : public ILocalizedTextSource
{
public:
	FGetLocalizedResources GetLocalizedResources;

private:
	virtual int32 GetPriority() const override { return ELocalizedTextSourcePriority::Highest; }
	virtual bool GetNativeCultureName(const ELocalizedTextSourceCategory InCategory, FString& OutNativeCultureName) override;
	virtual void GetLocalizedCultureNames(const ELocalizationLoadFlags InLoadFlags, TSet<FString>& OutLocalizedCultureNames) override;
	virtual void LoadLocalizedResources(
		const ELocalizationLoadFlags InLoadFlags, TArrayView<const FString> InPrioritizedCultures, FTextLocalizationResource& InOutNativeResource, FTextLocalizationResource& InOutLocalizedResource
	) override;
};
