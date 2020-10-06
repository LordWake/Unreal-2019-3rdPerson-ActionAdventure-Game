#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "ThrowingKnife.h"
#include "ShooterAnimInstance.h"
#include "Portal.h"
#include "GameFramework/Actor.h"
#include "ShooterEnemy.generated.h"

UCLASS()
class DEUTERONOMYANDROID_API AShooterEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	AShooterEnemy();

	UPROPERTY(EditAnywhere)
	APortal* portalReference;

	FVector socketLocation;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AThrowingKnife> prefabKnife;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool secondMesh;

protected:
	virtual void BeginPlay() override;

	UShooterAnimInstance* anim;
	USkeletalMeshComponent* myMesh;

	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent* damageParticle;

	UPROPERTY(EditAnywhere)
	float enemyLife;
	UPROPERTY(EditAnywhere)
	float attackCoolDown;
	UPROPERTY(BlueprintReadWrite)
	float distanceToAttack;
	UPROPERTY(BlueprintReadWrite)
	float distanceToPlayer;

	UPROPERTY(BlueprintReadOnly)
	bool isDead;
	UPROPERTY(BlueprintReadWrite)
	bool attackEnable;

	float attackTimer;

public:	
	virtual void Tick(float DeltaTime) override;

	void EnemyDead();
	void AttackThePlayer(float deltaTimer);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float damageValue);
	UFUNCTION(BlueprintCallable)
	void SpawnKnife();

	
};
