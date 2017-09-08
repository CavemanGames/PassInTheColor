// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/ResistenceWall.h"
#include "Components/BoxComponent.h"
#include "../PassInTheColorGameModeBase.h"


// Sets default values
AResistenceWall::AResistenceWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
}

// Called when the game starts or when spawned
void AResistenceWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResistenceWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation.X += Speed * DeltaTime;

	SetActorLocation(NewLocation);

	if (NewLocation.X < -600.0f)
	{
		this->Destroy();
		((APassInTheColorGameModeBase*)GetWorld()->GetAuthGameMode())->bIsWallSpawned = false;
	}
}

