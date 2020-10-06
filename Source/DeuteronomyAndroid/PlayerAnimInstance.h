#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"


UCLASS()
class DEUTERONOMYANDROID_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	
public:

	UPROPERTY(BlueprintReadOnly)
	FVector2D playerDirection;

	UPROPERTY(BlueprintReadOnly)
	bool onBlock;
	
	UPROPERTY(BlueprintReadWrite)
	bool attack_One;
	UPROPERTY(BlueprintReadWrite)
	bool attack_Two;
	UPROPERTY(BlueprintReadWrite)
	bool attack_Three;
	UPROPERTY(BlueprintReadWrite)
	bool attack_Four;

	UPROPERTY(BlueprintReadWrite)
	bool hard_One;
	UPROPERTY(BlueprintReadWrite)
	bool hard_Two;
	UPROPERTY(BlueprintReadWrite)
	bool hard_Three;
	UPROPERTY(BlueprintReadWrite)
	bool specialAttack;

	UPROPERTY(BlueprintReadWrite)
	bool underAttack;

	UPROPERTY(BlueprintReadOnly)
	bool isDead;


	void SetDirectionPlayer(FVector2D direction);
	void SetBlock(bool blocking);
	void SetNormalAttack(int attackNumber);
	void SetHardAttack(int hardNumber);
	void SetSpecialAttack();
	void SetPlayerTakeDamage();
	void SetPlayerDead();

};
