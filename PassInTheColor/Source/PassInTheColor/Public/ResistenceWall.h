// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResistenceWall.generated.h"

UCLASS()
class PASSINTHECOLOR_API AResistenceWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResistenceWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class UShapeComponent* RootBox;
	

	UPROPERTY(EditAnywhere)
		float Speed = 0.0f;
};
