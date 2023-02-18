// Copyright (c) Tolgee. All Rights Reserved.

#include "TolgeeLocalizationSubsystem.h"

#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "JsonObjectConverter.h"
#include "TolgeeLog.h"
#include "TolgeeSettings.h"
#include "TolgeeTextSource.h"

void UTolgeeLocalizationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TextSource = MakeShared<FTolgeeTextSource>();
	FTextLocalizationManager::Get().RegisterTextSource(TextSource.ToSharedRef());

	FWorldDelegates::OnWorldInitializedActors.AddLambda(
		[=](const UWorld::FActorsInitializedParams& Params)
		{
			FetchTranslation();
			FText TogleeTest = NSLOCTEXT("NamespaceTest", "KeyTest", "English Test");
			UE_LOG(LogTemp, Warning, TEXT("Simple Example: %s"), *TogleeTest.ToString());

			FText TogleeTest2 = FText::Format(NSLOCTEXT("NamespaceTest", "TimeFormat", "{0}|plural(one=time, other=times)"), 2);
			UE_LOG(LogTemp, Warning, TEXT("Complex Example: %s"), *TogleeTest2.ToString());
		}
	);
}
void UTolgeeLocalizationSubsystem::FetchTranslation()
{
	// TODO: Implement cursor for next requests in case it's too long
	const TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetHeader(TEXT("X-API-Key"), GetDefault<UTolgeeSettings>()->ApiKey);
	HttpRequest->SetURL(TEXT("https://app.tolgee.io/v2/projects/translations"));
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &ThisClass::OnTranslationFetched);
	HttpRequest->ProcessRequest();
}

void UTolgeeLocalizationSubsystem::OnTranslationFetched(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		UE_LOG(LogTolgee, Error, TEXT("Failed to fetch translation data"));
		return;
	}

	FTolgeeTranslationData Data;

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &Data);
	}
}