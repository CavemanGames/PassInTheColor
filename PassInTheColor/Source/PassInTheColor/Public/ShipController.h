// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Pawn.h"
#include "ShipController.generated.h"

UCLASS()
class PASSINTHECOLOR_API AShipController : public APawn
{
	GENERATED_BODY()

	//UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
		//class UShapeComponent* CollisionBox;

public:
	// Sets default values for this pawn's properties
	AShipController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		float Speed = 10.f;

	void Move_Forward(float AxisValue);
	void Move_Right(float AxisValue);
	void OnRestart();

	FVector CurrentVelocity;

	bool Died;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:

	float RotationValue = 0.f;
};
