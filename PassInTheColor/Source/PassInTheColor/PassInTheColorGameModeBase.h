// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PassInTheColorGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PASSINTHECOLOR_API APassInTheColorGameModeBase : public AGameMode
{
	GENERATED_BODY()
	

	float MINIMUM_INTERVAL = 0.5f;
	float MAXIMUM_INTERVAL = 2.0f;
	float TIME_TO_MINIMUM_INTERVAL = 30.0f;

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AColorToSpawn> ColorToSpawnBlueprint;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AResistenceWall> WallToSpawnBlueprint;

	float ColorTimer;
	float GameTimer;

	void IncrementScore();
	void OnGameOver();

	UFUNCTION(BlueprintCallable, Category = "UMGGame")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UPROPERTY(EditAnywhere, Category = "WallSpawn")
		bool bIsWallSpawned = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WallSpawn")
		float TimeToSpawnWall = 60;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WallSpawn")
		float TimeResistenceWall;

	bool bSpawnColor = true;

protected:

	int Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMGGame")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
		UUserWidget* CurrentWidget;

};
