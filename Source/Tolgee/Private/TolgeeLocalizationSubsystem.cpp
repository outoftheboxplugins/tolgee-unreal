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
			UE_LOG(LogTemp, Warning, TEXT("Simple Example: %s"), *TogleeTest.ToString());

			FText TogleeTest2 = FText::Format(NSLOCTEXT("NamespaceTest", "TimeFormat", "{0}|plural(one=time, other=times)"), 2);
			UE_LOG(LogTemp, Warning, TEXT("Complex Example: %s"), *TogleeTest2.ToString());
		}
	);
}