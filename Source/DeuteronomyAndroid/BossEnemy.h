#pragma once

#include "Engine.h"
#include "BossAnimInstance.h"
#include "Portal.h"
#include "GameFramework/Character.h"
#include "BossEnemy.generated.h"

UENUM(BlueprintType)
enum class EBehavioursBoss : uint8
{
	Follow UMETA(DisplayName = "Follow Target"),
	Idle UMETA(DisplayName = "Idle"),
	AttackPlayer UMETA(DisplayName = "Attack"),
};


UCLASS()
class DEUTERONOMYANDROID_API ABossEnemy : public ACharacter
{
	GENERATED_BODY()

public:

	ABossEnemy();

	UPROPERTY(EditAnywhere)
	APortal* portalReference;

	UPROPERTY(EditAnywhere, Category = Enum)
	EBehavioursBoss current;

	UPROPERTY(BlueprintReadWrite)
	UBoxComponent* normalTrigger;
	UPROPERTY(BlueprintReadWrite)
	UBoxComponent* hardTrigger;

	UPROPERTY(BlueprintReadWrite)
	float distanceToPlayer;

	UPROPERTY(EditAnywhere)
	float maxDistanceToGetCloser;

	UPROPERTY(BlueprintReadOnly)
	bool startTheAttack;

protected:

	virtual void BeginPlay() override;

	UBossAnimInstance* anim;
	USkeletalMeshComponent* myMesh;

	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent* damageParticle;
	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent* rockParticle;

	UPROPERTY(BlueprintReadWrite)
	bool catchPlayer;
	UPROPERTY(BlueprintReadWrite)
	bool onAttack;

	UPROPERTY(EditAnywhere)
	float followAgainCoolDown;
	UPROPERTY(EditAnywhere)
	float enemyLife;
	UPROPERTY(EditAnywhere)
	float attackAgainCoolDown;


	bool canFollow;
	bool isAttackAvailable;
	bool isDead;

	float followTimer;
	float canAttackTimer;

public:	

	virtual void Tick(float DeltaTime) override;
	void CheckCurrentState();
	void ChangeState();
	void FollowPlayer();
	void StartAttack();
	void AttackThePlayer();
	void FollowCoolDown(float deltaTimer);
	void AttackCoolDown(float deltaTimer);

	UFUNCTION(BlueprintCallable)
	void FollowAnimation(bool startFollow);
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float damageValue);
	UFUNCTION(BlueprintCallable)
	void SetNormalTrigger(bool turn);
	UFUNCTION(BlueprintCallable)
	void SetHardTrigger(bool turn);
	UFUNCTION(BlueprintCallable)
	void AttackRocksFX();

	void BossDead();
};
