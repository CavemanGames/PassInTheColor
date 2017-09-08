// Fill out your copyright notice in the Description page of Project Settings.

#include "PassInTheColorGameModeBase.h"
#include "Public/ColorToSpawn.h"
#include "Public/GameWidget.h"
#include "Public/ResistenceWall.h"

void APassInTheColorGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass);

	((UGameWidget*)CurrentWidget)->Load();

	TimeResistenceWall = TimeToSpawnWall;
}

void APassInTheColorGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GameTimer += DeltaSeconds;
	ColorTimer -= DeltaSeconds;

	//UE_LOG(LogTemp, Warning, TEXT("ColorTimer: %f"), ColorTimer);

	if (TimeResistenceWall > 0.f)
	{
		if (!bIsWallSpawned)
		{
			UWorld* World = GetWorld();

			if (World)
			{
				FVector Location = FVector(3000.0f, 0.f, 120.0f);

				World->SpawnActor<AResistenceWall>(WallToSpawnBlueprint, Location, FRotator::ZeroRotator);
				bIsWallSpawned = true;
			}
		}

		if (ColorTimer <= 0.0f)
		{
			float difficultyPercentage = FMath::Min(GameTimer / TIME_TO_MINIMUM_INTERVAL, 1.0f);

			ColorTimer = MAXIMUM_INTERVAL - (MAXIMUM_INTERVAL - MINIMUM_INTERVAL) * difficultyPercentage;

			UWorld* World = GetWorld();

			if (World)
			{
				FVector Location = FVector(800.0f, FMath::RandRange(-700.0f, 700.0f), 71.0f);

				World->SpawnActor<AColorToSpawn>(ColorToSpawnBlueprint, Location, FRotator::ZeroRotator);
			}
		}
		TimeResistenceWall -= DeltaSeconds;
	}
	else
	{
		for (TActorIterator<AResistenceWall> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
			AResistenceWall *Wall = *ActorItr;
			Wall->Speed = -200.0f;
		}

		GameTimer = 0.f;
		TimeResistenceWall = TimeToSpawnWall;
		//bIsWallSpawned = false;
	}

	IncrementScore();
	
}

void APassInTheColorGameModeBase::IncrementScore()
{
	Score += 1;
	((UGameWidget*)CurrentWidget)->SetScore(Score);
}

void APassInTheColorGameModeBase::OnGameOver()
{
	((UGameWidget*)CurrentWidget)->OnGameOver(Score);
}

void APassInTheColorGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
