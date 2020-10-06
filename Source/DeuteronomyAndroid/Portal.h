#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class DEUTERONOMYANDROID_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	APortal();

	UPROPERTY(EditAnywhere)
	int life;

protected:
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;
	void TakePortalDamage();
	void DestroyPortal();
	
};
