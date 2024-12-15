// Copyright Calathea Games

#pragma once // Ensures the file is only included once during compilation

#include "CoreMinimal.h" // Includes the core minimal set of headers required for Unreal Engine
#include "GameFramework/PlayerController.h" // Includes the base player controller class from Unreal Engine
#include "AuraPlayerController.generated.h" // Generates the necessary code for the AuraPlayerController class

// Forward declarations of classes and structs used in this file
class UInputMappingContext; // Forward declaration of UInputMappingContext class
class UInputAction; // Forward declaration of UInputAction class
struct FInputActionValue; // Forward declaration of FInputActionValue struct

/**
 * AAuraPlayerController class
 * Inherits from APlayerController, which is the base class for player controllers in Unreal Engine
 */
UCLASS() // Declares this class as an Unreal Engine class
class AURA_API AAuraPlayerController : public APlayerController // Declares the AAuraPlayerController class, which inherits from APlayerController
{
	GENERATED_BODY() // Macro that generates the boilerplate code needed for Unreal Engine classes

public:
	AAuraPlayerController(); // Constructor for the AAuraPlayerController class

protected:
	virtual void BeginPlay() override; // Override of the BeginPlay function, which is called when the game starts or when the actor is spawned
	virtual void SetupInputComponent() override; // Override of the SetupInputComponent function, which is used to set up the input bindings for the player controller

private:
	UPROPERTY(EditAnywhere, Category="Input") // Exposes the AuraContext property to the Unreal Editor, allowing it to be edited in the "Input" category
	TObjectPtr<UInputMappingContext> AuraContext; // Pointer to a UInputMappingContext, representing the input mapping context for the player controller

	UPROPERTY(EditAnywhere, Category="Input") // Exposes the MoveAction property to the Unreal Editor, allowing it to be edited in the "Input" category
	TObjectPtr<UInputAction> MoveAction; // Pointer to a UInputAction, representing the move action for the player controller

	void Move(const FInputActionValue& InputActionValue); // Function to handle the move action, takes a constant reference to an FInputActionValue as a parameter
};
