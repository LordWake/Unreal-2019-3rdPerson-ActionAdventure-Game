#include "PlayerAnimInstance.h"
#include "MyCharacter.h"

void UPlayerAnimInstance::SetDirectionPlayer(FVector2D direction)
{
	playerDirection = direction;
}

void UPlayerAnimInstance::SetBlock(bool blocking)
{
	onBlock = blocking;
}

void UPlayerAnimInstance::SetNormalAttack(int attackNumber)
{
	switch (attackNumber)
	{
		case 0:
		attack_One = true;
		break;

		case 1:
		attack_Two = true;
		break;

		case 2:
		attack_Three = true;
		break;

		case 3:
		attack_Four = true;
		break;
	}
}

void UPlayerAnimInstance::SetHardAttack(int hardNumber)
{
	switch (hardNumber)
	{
		case 0:
		hard_One = true;
		break;

		case 1:
		hard_Two = true;
		break;

		case 2:
		hard_Three = true;
		break;
	}
}

void UPlayerAnimInstance::SetPlayerTakeDamage()
{
	underAttack = true;
}

void UPlayerAnimInstance::SetPlayerDead()
{
	isDead = true;
}

void UPlayerAnimInstance::SetSpecialAttack()
{
	specialAttack = true;
}

