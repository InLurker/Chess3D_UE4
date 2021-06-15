#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ChessHUD.generated.h"

UCLASS()
class CHESS_API AChessHUD : public AHUD {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ChessUserWidget)
		class UChessPointsWidget* widgetPoint1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ChessUserWidget)
		class UChessPointsWidget* widgetPoint2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserWidget)
		class UChangeMaterialTab* MaterialSwitchingTab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserWidget)
		class UWinningScreenWidget* winningScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ReplayChessUserWidget)
		class UReplayChessUserWidget* replayUserWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projection2D)
		class UProjection2D* projection2DWidget;

public:
	AChessHUD();

	virtual void BeginPlay() override;

	void showWinningScreen();

	void showReplayScreen();
};