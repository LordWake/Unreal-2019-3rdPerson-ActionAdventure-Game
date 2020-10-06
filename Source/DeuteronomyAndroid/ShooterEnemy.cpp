#include "ShooterEnemy.h"

AShooterEnemy::AShooterEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShooterEnemy::BeginPlay()
{
	Super::BeginPlay();

	myMesh = FindComponentByClass<USkeletalMeshComponent>();
	if (myMesh)
		anim = Cast<UShooterAnimInstance>(myMesh->GetAnimInstance());
	
}

void AShooterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isDead) return;
	AttackThePlayer(DeltaTime);
}

void AShooterEnemy::TakeDamage(float damageValue)
{
	if (isDead) return;
	damageParticle->Activate(true);

	enemyLife = enemyLife - damageValue;

	if (enemyLife <= 0)
		EnemyDead();
	else
	{
		if (anim)
			anim->TakeDamageAnimation();
	}
}

void AShooterEnemy::EnemyDead()
{
	if (anim)
		anim->OnDeadState();
	
	portalReference->TakePortalDamage();
	isDead = true;
}

void AShooterEnemy::AttackThePlayer(float deltaTimer)
{
	if (!attackEnable) return;

	attackTimer += deltaTimer;
	if (attackTimer >= attackCoolDown)
	{
		if (anim)
			anim->AttackAnimation();

		attackTimer = 0;
	}
}

void AShooterEnemy::SpawnKnife()
{
	FActorSpawnParameters parameters;
	parameters.Owner = this;

	socketLocation = myMesh->GetSocketLocation("KnifeSpawner");

	GetWorld()->SpawnActor<AThrowingKnife>(prefabKnife, socketLocation, GetActorRotation(), parameters);
}


