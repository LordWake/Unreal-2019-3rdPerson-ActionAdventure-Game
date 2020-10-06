#include "MagicEnemyAnimInstance.h"

void UMagicEnemyAnimInstance::TakeDamageAnimation()
{
	onTakeDamage = true;
}

void UMagicEnemyAnimInstance::AttackAnimation()
{
	attackPlayer = true;
}

void UMagicEnemyAnimInstance::OnDeadState()
{
	enemyDead = true;
}

void UMagicEnemyAnimInstance::SpawnAnimation()
{
	enemySpawned = true;
}

void UMagicEnemyAnimInstance::ShotAnimation()
{
	shotPlayer = true;
}

