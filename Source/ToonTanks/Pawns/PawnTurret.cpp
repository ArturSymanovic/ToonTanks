// Copyright Artur Symanovic 2020

#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"
#include "PawnTurret.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorld()->GetTimerManager().SetTimer(
		FireRateTimeHandle, 
		this, 
		&APawnTurret::CheckFireCondition, 
		FireRate, 
		true, 
		false
	);
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || GetDistanceToPlayer() > FireRange)
	{
		return;
	}
	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	if (!PlayerPawn)
	{
		return;
	}

	//if player is in range fire and alive
	if (GetDistanceToPlayer() <= FireRange && PlayerPawn->IsPlayerAlive())
	{
		Fire();
	}
}

float APawnTurret::GetDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0.0f;
	}

	return (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
	//float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
}
