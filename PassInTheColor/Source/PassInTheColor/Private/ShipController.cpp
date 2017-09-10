// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/ShipController.h"
#include "Components/BoxComponent.h"
#include "../Public/ColorToSpawn.h"


// Sets default values
AShipController::AShipController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	//CollisionBox->bGenerateOverlapEvents = true;
	//CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AShipController::OnOverlap);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AShipController::BeginPlay()
{
	Super::BeginPlay();

	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	SetActorLocation(FVector(110, ((ViewportSize.Y / 1.617) / 2), 42));
}

// Called every frame
void AShipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() + Speed * CurrentVelocity * DeltaTime;
		const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		
		//UE_LOG(LogTemp, Warning, TEXT("ViewPort %f"), (ViewportSize.X));
		
		if (NewLocation.X > ((ViewportSize.X / 1.617)))
		{
			NewLocation.X = ((ViewportSize.X / 1.617));
		}
		if (NewLocation.X < 110)
		{
			NewLocation.X = 110;
		}

		if (NewLocation.Y > ((ViewportSize.Y / 1.617) - (80 * 1.617)))
		{
			NewLocation.Y = ((ViewportSize.Y / 1.617) - (80 * 1.617));
		}
		if (NewLocation.Y < 10)
		{
			NewLocation.Y = 10;
		}

		//UE_LOG(LogTemp, Warning, TEXT("%s"), *NewLocation.ToString());

		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void AShipController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AShipController::Move_Forward);
	PlayerInputComponent->BindAxis("Right", this, &AShipController::Move_Right);
	//PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AShipController::OnRestart).bExecuteWhenPaused = true;
}

void AShipController::Move_Forward(float AxisValue)
{
	float ClampedSpeed = FMath::Clamp<float>(AxisValue, -1, 1);
	CurrentVelocity.X = ClampedSpeed * 100.0f;
}

void AShipController::Move_Right(float AxisValue)
{
	float ClampedSpeed = FMath::Clamp<float>(AxisValue, -1, 1);
	CurrentVelocity.Y = ClampedSpeed * 100.0f;
	FRotator ShipRotation = GetActorForwardVector().Rotation();
	RotationValue += AxisValue;
	// Set Rotation of ship when move Right
	ShipRotation.Roll += RotationValue * 10.f;
	SetActorRelativeRotation(ShipRotation);

}

void AShipController::OnRestart()
{
	/*if (Died)
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}*/
}

void AShipController::OnOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	/*if (OtherActor->IsA(AColorToSpawn::StaticClass()))
	{


		this->SetActorHiddenInGame(true);

		
	}
	
	if (OtherActor->IsA(AColorToSpawn::StaticClass()))
	{
		//Died = true;

		this->SetActorHiddenInGame(true);

		((ASpaceShooterGameMode*)GetWorld()->GetAuthGameMode())->OnGameOver();

		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}//*/
}

