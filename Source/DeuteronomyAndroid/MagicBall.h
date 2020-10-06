#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "MagicBall.generated.h"

UCLASS()
class DEUTERONOMYANDROID_API AMagicBall : public AActor
{
	GENERATED_BODY()
	
public:	
	AMagicBall();

	UPROPERTY(EditAnywhere)
	float speed;
	UPROPERTY(EditAnywhere)
	float deadLimit;

	float deadTimer;

	UPROPERTY(BlueprintReadOnly)
	bool forceDead;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void MoveThisMagicBall(float deltaTimer);
	void CheckLifeTime(float deltaTimer);

	
	
};
