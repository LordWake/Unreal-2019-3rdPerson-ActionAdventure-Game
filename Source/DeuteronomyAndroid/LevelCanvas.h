#pragma once

#include "Engine.h"
#include "MyUserWidget.h"
#include "GameFramework/PlayerController.h"
#include "LevelCanvas.generated.h"

UCLASS()
class DEUTERONOMYANDROID_API ALevelCanvas : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMyUserWidget> prefabCanvas;

	UPROPERTY(BlueprintReadOnly)
	UMyUserWidget* canvas;

	void virtual BeginPlay() override;

	void UpdatePlayerLife(float life);
	void UpdatePlayerPower(float power);
	void PlayerGameOver(int gameOverLevel);
	
	UFUNCTION(BlueprintCallable)
	void LoadNextLevel(int level);
	UFUNCTION(BlueprintCallable)
	void HideCanvas(bool hide);
	
};
