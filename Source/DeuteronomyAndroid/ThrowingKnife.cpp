#include "ThrowingKnife.h"


AThrowingKnife::AThrowingKnife()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AThrowingKnife::BeginPlay()
{
	Super::BeginPlay();
	
}

void AThrowingKnife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveThisKnife(DeltaTime);
	CheckLifeTime(DeltaTime);
}

void AThrowingKnife::MoveThisKnife(float deltaTimer)
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * deltaTimer);
}

void AThrowingKnife::CheckLifeTime(float deltaTimer)
{
	deadTimer += deltaTimer;
	if (deadTimer >= deadLimit)
		forceDead = true;
}

