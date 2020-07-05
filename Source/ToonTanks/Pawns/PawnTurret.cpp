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

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APawnTurret::CheckFireCondition()
{
	//If player is null or dead return
	if (!PlayerPawn)
	{
		return;
	}
	//if player is in range fire
	if (GetDistanceToPlayer() <= FireRange)
	{
		//Fire
		UE_LOG(LogTemp, Warning, TEXT("%s: Fire"), *GetName());
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
