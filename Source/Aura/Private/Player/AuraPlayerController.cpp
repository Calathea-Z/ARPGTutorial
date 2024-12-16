// Copyright Calathea Games

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

// Constructor for the AAuraPlayerController class
AAuraPlayerController::AAuraPlayerController()
{
    bReplicates = true; // Enable replication for this player controller
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);

    CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
    FHitResult CursorHit;
    GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
    if (!CursorHit.bBlockingHit) return;
    LastActor = ThisActor;
    ThisActor = CursorHit.GetActor();

    if (LastActor == nullptr)
    {
        if (ThisActor != nullptr)
        {
            ThisActor->HighlightActor();
        }
    }
    else
    {
        if (ThisActor == nullptr)
        {
            LastActor->UnHighlightActor();
        }
        else
        {
            if (LastActor != ThisActor)
            {
                LastActor->UnHighlightActor();
                ThisActor->HighlightActor();
            }
        }
    }
}

// Called when the game starts or when the player controller is spawned
void AAuraPlayerController::BeginPlay()
{
    Super::BeginPlay(); // Call the base class BeginPlay
    check(AuraContext); // Ensure that AuraContext is valid

    // Get the enhanced input subsystem for the local player
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    check(Subsystem); // Ensure that the subsystem is valid
    Subsystem->AddMappingContext(AuraContext, 0); // Add the input mapping context

    bShowMouseCursor = true; // Show the mouse cursor
    DefaultMouseCursor = EMouseCursor::Default; // Set the default mouse cursor
    FInputModeGameAndUI InputModeData; // Create an input mode for game and UI
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // Do not lock the mouse to the viewport
    InputModeData.SetHideCursorDuringCapture(false); // Do not hide the cursor during capture
    SetInputMode(InputModeData); // Apply the input mode
}

// Set up the input component for the player controller
void AAuraPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent(); // Call the base class SetupInputComponent

    // Cast the input component to UEnhancedInputComponent
    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

    // Bind the MoveAction to the Move function
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

// Handle the move action
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
    // Get the input axis vector from the input action value
    const FVector2d InputAxisVector = InputActionValue.Get<FVector2D>();
    const FRotator Rotation = GetControlRotation(); // Get the current control rotation
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.0f); // Create a yaw rotation with zero pitch and roll

    // Calculate the forward and right directions based on the yaw rotation
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

    // If there is a controlled pawn, add movement input based on the input axis vector
    if (APawn* ControlledPawn = GetPawn<APawn>())
    {
        ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y); // Move forward/backward
        ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X); // Move right/left
    }
}
