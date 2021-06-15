#include "ChessPointsWidget.h"
#include "WinningScreenWidget.h"
#include <string>
#include <Components/TextBlock.h>

void UChessPointsWidget::addScore(int32 amount) {
	currentPoint += amount;

	FString updatePlayerPoint = FString::FromInt(currentPoint);;
	updatePlayerPoint += " Points";

	PlayerPointText = FText::FromString(updatePlayerPoint);
	
	if(PlayerPointTextBlock != nullptr)
		PlayerPointTextBlock->SetText(PlayerPointText);
}
