#pragma once

#include "Engine.h"
#include "FightEnemyAnimInstance.h"
#include "Portal.h"
#include "GameFramework/Character.h"
#include "MyFightEnemy.generated.h"

UENUM(BlueprintType)
enum class EBehavioursEnemy :uint8
{
	Follow UMETA(DisplayName = "Follow Target"),
	Idle UMETA(DisplayName = "Idle"),
	AttackPlayer UMETA(DisplayName = "Attack Player"),
};

UCLASS()
class DEUTERONOMYANDROID_API AMyFightEnemy : public ACharacter
{
	GENERATED_BODY()

public:

	AMyFightEnemy();

	UPROPERTY(EditAnywhere)
	APortal* portalReference;

	UPROPERTY(EditAnywhere, Category = Enum)
	EBehavioursEnemy current;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool secondMesh;

protected:

	virtual void BeginPlay() override;
	
	UFightEnemyAnimInstance* anim;
	USkeletalMeshComponent* myMesh;

	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent* damageParticle;

	UPROPERTY(BlueprintReadWrite)
	bool catchPlayer; //Utilizado desde el blueprint para informar a la IA si seguir al player o frenar el movimiento.
	UPROPERTY(BlueprintReadWrite)
	bool isFront; //Utilizado para saber la direccion en la que estamos siendo atacados.
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

	int hardAttackChance;

public:	

	virtual void Tick(float DeltaTime) override;

	void CheckCurrentState();
	void ChangeState();
	void FollowPlayer();
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

	void EnemyDead();
	
};
