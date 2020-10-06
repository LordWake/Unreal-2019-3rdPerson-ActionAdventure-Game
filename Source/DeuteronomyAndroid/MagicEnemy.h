#pragma once

#include "Engine.h"
#include "Portal.h"
#include "MagicBall.h"
#include "MagicEnemyAnimInstance.h"
#include "GameFramework/Actor.h"
#include "MagicEnemy.generated.h"

UCLASS()
class DEUTERONOMYANDROID_API AMagicEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	AMagicEnemy();

	UPROPERTY(EditAnywhere)
	APortal* portalReference;

	UPROPERTY(BlueprintReadOnly)
	bool startTheAttack;

	UPROPERTY(BlueprintReadWrite)
	bool onAttack;

	FVector socketLocation;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMagicBall> prefabMagicBall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor *> blockWalls;

protected:
	virtual void BeginPlay() override;

	UMagicEnemyAnimInstance* anim;
	USkeletalMeshComponent* myMesh;

	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent* damageParticle;

	UPROPERTY(BlueprintReadWrite)
	UBoxComponent* boxTrigger;

	float attackTimer;
	
	UPROPERTY(EditAnywhere)
	float attackCoolDown;

	UPROPERTY(EditAnywhere)
	float distanceToAttack;
	
	UPROPERTY(BlueprintReadWrite)
	float distanceToPlayer;

	UPROPERTY(EditAnywhere)
	float enemyLife;

	UPROPERTY(BlueprintReadOnly)
	bool isDead;



public:	
	virtual void Tick(float DeltaTime) override;

	void EnemyDead();
	void ChooseAttack(float deltaTimer);
	void MeleeAttack();
	void MagicAttack();

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float damageValue);
	UFUNCTION(BlueprintCallable)
	void OnSpawnAnimation();

	UFUNCTION(BlueprintCallable)
	void SetAttackTrigger(bool turn);
	UFUNCTION(BlueprintCallable)
	void SpawnMagicShot();


	
	
};
