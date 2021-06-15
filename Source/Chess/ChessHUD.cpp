#include "ChessHUD.h"
#include "ChessController.h"
#include "ChessPointsWidget.h"
#include "WinningScreenWidget.h"
#include "ReplayChessUserWidget.h"

AChessHUD::AChessHUD() {
}

void AChessHUD::BeginPlay() {
	Super::BeginPlay();
}

void AChessHUD::showWinningScreen() {
	winningScreen->AddToViewport();
}

void AChessHUD::showReplayScreen() {
	winningScreen->RemoveFromViewport();

	replayUserWidget->AddToViewport();
}