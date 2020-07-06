// Copyright Artur Symanovic 2020

#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Health = DefaultHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	Owner = GetOwner();

	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HealthComponent has no reference to the owmer!"));
	}
	
}

void UHealthComponent::TakeDamage(
	AActor* DamageActor, 
	float Damage, 
	const UDamageType* DamageType, 
	AController* InstigatedBy, 
	AActor* DamageCauser
)
{
	if (Damage == 0 || Health == 0)
	{
		return;
	}
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	if (Health <= 0)
	{
		if (GameModeRef)
		{
			GameModeRef->ActorDied(Owner);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("HealthComponent has no reference to the owmer!"));
		}
	}
}
