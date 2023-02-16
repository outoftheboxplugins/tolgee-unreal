#pragma once

#include "Subsystems/EngineSubsystem.h"

#include "TolgeeLocalizationSubsystem.generated.h"

class FTolgeeTextSource;

/**
 *
 */
UCLASS()
class TOLGEE_API UTolgeeLocalizationSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	TSharedPtr<FTolgeeTextSource> TextSource;
};
