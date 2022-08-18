// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

APawnTank::APawnTank()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
}

void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.f, 12, FColor::Blue);
		LookAtTarget(HitResult.ImpactPoint);
	}
}

void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::MoveForward(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void APawnTank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * RotationRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}
