// Fill out your copyright notice in the Description page of Project Settings.

#include "PassInTheColorGameModeBase.h"
#include "Public/ColorToSpawn.h"
#include "Public/GameWidget.h"
#include "Public/ResistenceWall.h"

void APassInTheColorGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	TimeResistenceWall = TimeToSpawnWall;
}

void APassInTheColorGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (!bIsMenuOpen)
	{
		GameTimer += DeltaSeconds;
		ColorTimer -= DeltaSeconds;

		//UE_LOG(LogTemp, Warning, TEXT("ColorTimer: %f"), ColorTimer);


		if (!bIsWallSpawned)
		{
			UWorld* World = GetWorld();

			if (World)
			{
				FVector Location = FVector(1500.0f, 0.f, 120.0f);

				World->SpawnActor<AResistenceWall>(WallToSpawnBlueprint, Location, FRotator::ZeroRotator);
				bIsWallSpawned = true;
			}
		}
		if (TimeResistenceWall <= 0.f)
		{
			for (TActorIterator<AResistenceWall> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
				AResistenceWall *Wall = *ActorItr;
				if (Wall->Speed == 0.f)
				{
					Wall->Speed = -400.0f;
					bSpawnColor = false;
				}
			}
		}

		if (bSpawnColor)
		{
			if (ColorTimer <= 0.0f)
			{
				float difficultyPercentage = FMath::Min(GameTimer / TIME_TO_MINIMUM_INTERVAL, 1.0f);

				ColorTimer = MAXIMUM_INTERVAL - (MAXIMUM_INTERVAL - MINIMUM_INTERVAL) * difficultyPercentage;

				UWorld* World = GetWorld();

				if (World)
				{
					FVector Location = FVector(1200.0f, FMath::RandRange(0.f, 500.0f), 71.0f);

					World->SpawnActor<AColorToSpawn>(ColorToSpawnBlueprint, Location, FRotator::ZeroRotator);
				}
			}
			TimeResistenceWall -= DeltaSeconds;
		}
		//UE_LOG(LogTemp, Warning, TEXT("%f"), TimeResistenceWall);
	//IncrementScore();
	}
}

void APassInTheColorGameModeBase::IncrementScore(int Value)
{
	Score += Value;
	//((UGameWidget*)CurrentWidget)->SetScore(Score);
}

void APassInTheColorGameModeBase::AddGameHUD()
{
	//ChangeMenuWidget(StartingWidgetClass);
	//((UGameWidget*)CurrentWidget)->Load();
}

void APassInTheColorGameModeBase::OnGameOver()
{
	//((UGameWidget*)CurrentWidget)->OnGameOver(Score);
}

void APassInTheColorGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (!bIsMenuOpen)
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
}
