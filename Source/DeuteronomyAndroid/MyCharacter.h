#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "LevelCanvas.h"
#include "PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class DEUTERONOMYANDROID_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AMyCharacter();

	UPROPERTY(BlueprintReadWrite)
	FVector2D movementDirection;
	UPlayerAnimInstance* anim;
	USkeletalMeshComponent * myMesh;

	UPROPERTY(EditAnywhere)
	float zoomCameraSpeed;
	UPROPERTY(EditAnywhere)
	float minCamZoom;
	UPROPERTY(EditAnywhere)
	float maxCamZoom;

	UPROPERTY(BlueprintReadOnly)
	bool onBlockState;
	UPROPERTY(BlueprintReadWrite)
	bool canMove;
	UPROPERTY(BlueprintReadWrite)
	bool canAttack;
	UPROPERTY(BlueprintReadWrite)
	bool outOfCombat;
	UPROPERTY(BlueprintReadWrite)
	bool onDamage;
	UPROPERTY(BlueprintReadWrite)
	bool onCinematic;
	UPROPERTY(BlueprintReadOnly)
	bool playerIsDead;

	bool doZoom;
	bool startTheCameraZoom;

	int normalAttackCount;
	int hardAttackCount;
	UPROPERTY(BlueprintReadWrite)
	int currentLevelChecker;

	UPROPERTY(BlueprintReadWrite)
	UBoxComponent* normalTrigger;
	UPROPERTY(BlueprintReadWrite)
	UBoxComponent* hardTrigger;
	UPROPERTY(BlueprintReadWrite)
	UBoxComponent* specialTrigger;

	float timerZoomCombat;

	USpringArmComponent* cameraHandler;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float maxLife;
	float life;

	float powerAmount;
	UPROPERTY(EditAnywhere)
	float maxPowerAmount;

	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent* damageParticle;
	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent* hardDamageParticle;

	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* blockAudio;


public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MovePlayerAnimation(FVector2D myDirection);
	void CameraZoom();
	void BlockAttacks();
	void UnblockAttacks();
	void NormalAttackCombo();
	void HardAttackCombo();
	void SpecialAttack();
	void ReleaseCameraZoom();
	void UpdateHUDLife();
	void UpdateHUDPower();

	UFUNCTION(BlueprintCallable)
	void NormalTriggerOn();
	UFUNCTION(BlueprintCallable)
	void NormalTriggerOff();
	UFUNCTION(BlueprintCallable)
	void HardTriggerOn();
	UFUNCTION(BlueprintCallable)
	void HardTriggerOff();
	UFUNCTION(BlueprintCallable)
	void SpecialTriggerSwitch(bool turn);
	
	UFUNCTION(BlueprintCallable)
	void NormalTakeDamage(float damageValue);
	UFUNCTION(BlueprintCallable)
	void HardTakeDamage(float damageValue);
	UFUNCTION(BlueprintCallable)
	void  TakePowerDamage(float damageValue);
	
	UFUNCTION(BlueprintCallable)
	void TakePower(float powerValue);
	UFUNCTION(BlueprintCallable)
	void NotifyGameOver();
	UFUNCTION(BlueprintCallable)
	void NotifyCinematicFinish();
	UFUNCTION(BlueprintCallable)
	void NotifyCinematicStart();

	void PlayerDead();
	
};
