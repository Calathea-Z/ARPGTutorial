// Copyright Calathea Games


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetControllerClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OverlayWidgetControllerClass is null! Ensure it's set in BP_AuraHUD or via code."));
		return nullptr;
	}

	
	// Check if the OverlayWidgetController is already created
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		
		if (OverlayWidgetController)
		{
			OverlayWidgetController->SetWidgetControllerParams(WCParams);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to create OverlayWidgetController!"));
		}
	}

	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// Validate Blueprint properties
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"))
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"))

	// Ensure valid world reference
	if (!GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("GetWorld() returned nullptr in InitOverlay!"));
		return;
	}

	// Create and cast the Widget
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	if (OverlayWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create OverlayWidget! Check OverlayWidgetClass."));
		return;
	}

	// Create Widget Controller
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	if (WidgetController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("OverlayWidgetController is null! Check overlay configuration."));
		return;
	}

	OverlayWidget->SetWidgetController(WidgetController);

	WidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}
