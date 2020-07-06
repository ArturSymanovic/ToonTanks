// Copyright Artur Symanovic 2020

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PawnTank.h"

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();
	
	bAlive = false;

	SetActorHiddenInGame(true);

	SetActorTickEnabled(false);
	//TODO Create separate function for player hiding
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Rotate();
	Move();
	if (PlayerControllerRef)
	{
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;
		RotateTurret(HitLocation);
	}	
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

bool APawnTank::IsPlayerAlive() const
{
	return bAlive;
}

void APawnTank::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0.0f, 0.0f);
}

void APawnTank::CalculateRotateInput(float Value)
{
	float RotationAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0.0f, RotationAmount, 0.0f);
	RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}
