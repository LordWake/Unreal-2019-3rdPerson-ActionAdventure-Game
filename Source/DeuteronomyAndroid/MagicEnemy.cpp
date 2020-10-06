
#include "MagicEnemy.h"


AMagicEnemy::AMagicEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMagicEnemy::BeginPlay()
{
	Super::BeginPlay();

	myMesh = FindComponentByClass<USkeletalMeshComponent>();
	if (myMesh)
		anim = Cast<UMagicEnemyAnimInstance>(myMesh->GetAnimInstance());
	
}

void AMagicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!startTheAttack) return;
	ChooseAttack(DeltaTime);
}

void AMagicEnemy::TakeDamage(float damageValue)
{
	if (isDead) return;
	damageParticle->Activate(true);

	enemyLife = enemyLife - damageValue;

	if (enemyLife <= 0)
		EnemyDead();
	else
	{
		if (!onAttack)
		{
			if (anim)
			anim->TakeDamageAnimation();
		}
	}
}

void AMagicEnemy::EnemyDead()
{
	if (anim)
		anim->OnDeadState();

	portalReference->TakePortalDamage();

	isDead = true;
}

void AMagicEnemy::OnSpawnAnimation()
{
	if (anim)
		anim->SpawnAnimation();
}

void AMagicEnemy::ChooseAttack(float deltaTimer)
{
	attackTimer += deltaTimer;
	
	if (attackTimer >= attackCoolDown)
	{
		if (distanceToPlayer <= distanceToAttack)
			MeleeAttack();
		else
			MagicAttack();

		attackTimer = 0;
	}
}

void AMagicEnemy::MeleeAttack()
{
	onAttack = true;
	if (anim)
		anim->AttackAnimation();
}

void AMagicEnemy::MagicAttack()
{
	onAttack = true;
	if (anim)
		anim->ShotAnimation();
}

void AMagicEnemy::SetAttackTrigger(bool turn)
{
	if (turn)
		boxTrigger->SetGenerateOverlapEvents(true);
	else
		boxTrigger->SetGenerateOverlapEvents(false);
}

void AMagicEnemy::SpawnMagicShot()
{
	FActorSpawnParameters parameters;
	parameters.Owner = this;

	socketLocation = myMesh->GetSocketLocation("SpawnerBall");
	GetWorld()->SpawnActor<AMagicBall>(prefabMagicBall, socketLocation, GetActorRotation(), parameters);
}

