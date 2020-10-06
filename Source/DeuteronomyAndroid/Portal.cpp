#include "Portal.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal::TakePortalDamage()
{
	life--;
	if (life <= 0)
		DestroyPortal();
}

void APortal::DestroyPortal()
{
	Destroy(true);
}

