// Copyright Artur Symanovic 2020

#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay()
{
	TargetTurrets = GetTargetTurretsCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart();

	Super::BeginPlay();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	
	if (DeadActor == PlayerTank)
	{
		PlayerTank->PawnDestroyed();
		HandleGameOver(false);
		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->PawnDestroyed();
		TargetTurrets--;
		if (TargetTurrets == 0) 
		{
			HandleGameOver(true);
		}
	}
}

void ATankGameModeBase::HandleGameStart()
{
	GameStart();

	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);
		FTimerHandle PlayerEnableHandle;

		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
		
		GetWorldTimerManager().SetTimer(
			PlayerEnableHandle,
			PlayerEnableDelegate,
			StartDelay,
			false
		);
	}
	
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
	//See if the player has destroyed all turrets, show win result.
	//else if turret destroyed the player, show lose result.
	//Call Blueprint version of GameOver()
}

int32 ATankGameModeBase::GetTargetTurretsCount()
{
	TSubclassOf<APawnTurret> ClassToFind;
	ClassToFind = APawnTurret::StaticClass();
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TurretActors);
	return TurretActors.Num();
}
