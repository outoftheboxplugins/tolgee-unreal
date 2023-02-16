#include "TolgeeLocalizationSubsystem.h"

#include "TolgeeTextSource.h"

void UTolgeeLocalizationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TextSource = MakeShared<FTolgeeTextSource>();
	FTextLocalizationManager::Get().RegisterTextSource(TextSource.ToSharedRef());

	FWorldDelegates::OnWorldInitializedActors.AddLambda(
		[](const UWorld::FActorsInitializedParams& Params)
		{
			FText TogleeTest = NSLOCTEXT("NamespaceTest", "KeyTest", "English Test");
			UE_LOG(LogTemp, Warning, TEXT("%s"), *TogleeTest.ToString())
		}
	);
}