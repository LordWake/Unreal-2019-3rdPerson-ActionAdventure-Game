#include "ShooterAnimInstance.h"

void UShooterAnimInstance::TakeDamageAnimation()
{
	underAttack = true;
}

void UShooterAnimInstance::OnDeadState()
{
	enemyDead = true;
}

void UShooterAnimInstance::AttackAnimation()
{
	attackPlayer = true;
}


