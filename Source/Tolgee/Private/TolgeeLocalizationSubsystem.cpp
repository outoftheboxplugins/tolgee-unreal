// Copyright (c) Tolgee. All Rights Reserved.

#include "TolgeeLocalizationSubsystem.h"

#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Internationalization/TextLocalizationResource.h"
#include "JsonObjectConverter.h"
#include "TolgeeLog.h"
#include "TolgeeSettings.h"
#include "TolgeeTextSource.h"

void UTolgeeLocalizationSubsystem::ManualFetch()
{
	UE_LOG(LogTolgee, Log, TEXT("UTolgeeLocalizationSubsystem::ManualFetch"));

	FetchTranslation();
}

void UTolgeeLocalizationSubsystem::GetLocalizedResources(
	const ELocalizationLoadFlags InLoadFlags, TArrayView<const FString> InPrioritizedCultures, FTextLocalizationResource& InOutNativeResource, FTextLocalizationResource& InOutLocalizedResource
) const
{
	// TODO: Maybe use tags to get the InSourceString
	// TODO: We need a way to gather every localized key from Unreal and upload it to Tolgee web
	for (const TSharedPtr<FJsonValue>& TranslatedKey : TranslatedKeys)
	{
		const TSharedRef<FJsonObject> TranslatedKeyObject = TranslatedKey->AsObject().ToSharedRef();

		FTolgeeKey Key;
		FJsonObjectConverter::JsonObjectToUStruct(TranslatedKeyObject, &Key);

		consteTSharedRef<FJsonObject> Translations = TranslatedKeyObject->GetObjectField("translations").ToSharedRef();

		FTolgeeTranslation DefaultLanguage;
		FJsonObjectConverter::JsonObjectToUStruct(Translations->GetObjectField("en").ToSharedRef(), &DefaultLanguage);

		// TODO: could not get german, we should check what payload we get.
		FTolgeeTranslation CurrentLanguage;
		FJsonObjectConverter::JsonObjectToUStruct(Translations->GetObjectField("translations")->GetObjectField("de").ToSharedRef(), &DefaultLanguage);

		FTextKey InNamespace = Key.KeyNamespace;
		FTextKey InKey = Key.KeyName;
		FString InSourceString = DefaultLanguage.Text;
		FString InLocalizedString = CurrentLanguage.Text;

		InOutLocalizedResource.AddEntry(InNamespace, InKey, InSourceString, InLocalizedString, 0);
	}
}

void UTolgeeLocalizationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTolgee, Log, TEXT("UTolgeeLocalizationSubsystem::Initialize"));

	Super::Initialize(Collection);

	GetGameInstance()->GetTimerManager().SetTimer(AutoFetchTimerHandle, this, &ThisClass::FetchTranslation, GetDefault<UTolgeeSettings>()->UpdateInterval, true, 0.1f);

	TextSource = MakeShared<FTolgeeTextSource>();
	TextSource->GetLocalizedResources.BindUObject(this, &ThisClass::GetLocalizedResources);
	FTextLocalizationManager::Get().RegisterTextSource(TextSource.ToSharedRef());

	FetchTranslation();

	TestPrint();
}
void UTolgeeLocalizationSubsystem::FetchTranslation()
{
	UE_LOG(LogTolgee, Verbose, TEXT("UTolgeeLocalizationSubsystem::FetchTranslation"));

	TranslatedKeys.Empty();

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
	UE_LOG(LogTolgee, Verbose, TEXT("UTolgeeLocalizationSubsystem::OnTranslationFetched"));

	// TODO: Fetch only one project, which is set in settings
	if (!bWasSuccessful)
	{
		UE_LOG(LogTolgee, Error, TEXT("Request to fetch translations was unsuccessful."));
		return;
	}
	if (!EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		UE_LOG(LogTolgee, Error, TEXT("Request to fetch translation received unexpected code: %s"), *LexToString(Response->GetResponseCode()));
		return;
	}

	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
	if (!FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		UE_LOG(LogTolgee, Error, TEXT("Could not deserialize response: %s"), *LexToString(Response->GetResponseCode()));
		return;
	}

	FString NextCursor = JsonObject->GetStringField("nextCursor");
	TSharedPtr<FJsonObject> EmbeddedData = JsonObject->GetObjectField("_embedded");
	TranslatedKeys.Append(EmbeddedData->GetArrayField("keys"));

	// TODO: Only update the fetched data after all the translation were received (no more cursor)
	OnTranslationReady();
}

void UTolgeeLocalizationSubsystem::OnTranslationReady()
{
	UE_LOG(LogTolgee, Verbose, TEXT("UTolgeeLocalizationSubsystem::OnTranslationReady"));

	FTextLocalizationManager::Get().RefreshResources();

	TestPrint();
}

void UTolgeeLocalizationSubsystem::TestPrint()
{
	FText TogleeTest = NSLOCTEXT("NamespaceTest", "KeyTest", "English Test");
	UE_LOG(LogTemp, Warning, TEXT("Simple Example: %s"), *TogleeTest.ToString());

	FText TogleeTest2 = FText::Format(NSLOCTEXT("NamespaceTest", "TimeFormat", "{0}|plural(one=time, other=times)"), 2);
	UE_LOG(LogTemp, Warning, TEXT("Complex Example: %s"), *TogleeTest2.ToString());
}
