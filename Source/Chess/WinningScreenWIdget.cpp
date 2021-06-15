#include "WinningScreenWidget.h"
#include "UMG/Public/Components/Button.h"
#include "ChessPlayer.h"
#include "ReplayChessUserWidget.h"
#include "Components/TextBlock.h"
#include "ChessPiece_Base.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "ChessController.h"
#include "tile.h"
#include "ChessHUD.h"
#include "ChessPointsWidget.h"
#include "Projection2D.h"

void UWinningScreenWidget::NativeConstruct() {
	Super::NativeConstruct();
	ToReplayButton->OnClicked.AddDynamic(this, &UWinningScreenWidget::OnClick_ToReplayScreen);
	NewGameButton->OnClicked.AddDynamic(this, &UWinningScreenWidget::ResetGame);
	ExitButton->OnClicked.AddDynamic(this, &UWinningScreenWidget::ExitGame);
}

void UWinningScreenWidget::OnClick_ToReplayScreen() {
	ReplayScreen->AddToViewport();
	ReplayScreen->ScanMatchRecords();
}

void UWinningScreenWidget::SetWinner(FString winner) {
	WinnerTextBlock->SetText(FText::FromString(winner));
}

void UWinningScreenWidget::ResetGame() {
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Atile::StaticClass(), FoundActors);
	for (AActor* Pieces : FoundActors) {
		(Cast <Atile>(Pieces))->unoccupy();
	}
	FoundActors.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChessPiece_Base::StaticClass(), FoundActors);
	for (AActor* Pieces : FoundActors) {
		(Cast <AChessPiece_Base>(Pieces))->ResetTiling();
		(Cast <AChessPiece_Base>(Pieces))->Reset();
		(Cast <AChessPiece_Base>(Pieces))->neverMove = true;
	}
	this->RemoveFromParent();
	AChessController* controller = Cast <AChessController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->endGame = false;
	AChessHUD* HUD = Cast <AChessHUD>(controller->GetHUD());
	HUD->widgetPoint1->addScore(controller->GetPlayerOne()->getScore() * -1);
	HUD->widgetPoint2->addScore(controller->GetPlayerTwo()->getScore() * -1);
	HUD->projection2DWidget->reset2DBoard();
	(controller->GetPlayerOne())->addScore(controller->GetPlayerOne()->getScore() * -1);
	(controller->GetPlayerTwo())->addScore(controller->GetPlayerTwo()->getScore() * -1);
	controller->CurrentPlayer = controller->GetPlayerOne();
	controller->Possess((APawn*) controller->GetPlayerOne());
	
}

void UWinningScreenWidget::ExitGame() {
	GetWorld()->Exec(GetWorld(), TEXT("Exit"));
}