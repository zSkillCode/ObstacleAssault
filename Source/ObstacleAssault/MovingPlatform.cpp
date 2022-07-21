// © SkillCode - All Rights Reserved.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	const FString MyString = GetName();
	UE_LOG(LogTemp, Display, TEXT("Moving Platform created: %s"), *MyString);
}

// Called every frame
void AMovingPlatform::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(const float DeltaTime)
{
	if (ShouldPlatformReturn())
	{
		const FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation += MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);

		PlatformVelocity *= -1;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		// If PlatformVelocity is (100, 0, 0) then this will move the platform 100 units per second.
		CurrentLocation += PlatformVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(const float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}


bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}
