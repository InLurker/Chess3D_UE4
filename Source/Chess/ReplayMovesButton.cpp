#include "ReplayMovesButton.h"
#include "ReplayChessUserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"

UReplayMovesButton::UReplayMovesButton() {
    OnClicked.AddDynamic(this, &UReplayMovesButton::OnClick);
}

void UReplayMovesButton::OnClick() {
    ResetPiecesPosition();
    for (int i = 0; i <= index; ++i) {
        FString fromCoordinate;
        FString toCoordinate;
        UReplayMovesButton* playbackMoveNow = Cast <UReplayMovesButton>(OwningWidget->MovesScrollBox->GetChildAt(i));
        fromCoordinate = playbackMoveNow->From;
        toCoordinate = playbackMoveNow->To;
        if (playbackMoveNow->take) {
            for (int j = 0; j < 32; ++j) {
                FVector2D coordinate = (Cast <UCanvasPanelSlot>(OwningWidget->ChessPieces[j]->Slot))->GetPosition();
                if (coordinate == FVector2D(int32(-324 + (int32(toCoordinate[0] - 'A') * 81)), int32(300 - (int32(toCoordinate[1] - '1') * 81))) && OwningWidget->ChessPieces[j]->GetRenderOpacity() == 1) {
                    OwningWidget->ChessPieces[j]->SetRenderOpacity(0);
                    break;
                }
            }
        }
        for (int j = 0; j < 32; ++j) {
            UCanvasPanelSlot* ImageInCanvas = Cast <UCanvasPanelSlot> (OwningWidget->ChessPieces[j]->Slot);
            FVector2D coordinate = ImageInCanvas->GetPosition();
            if (coordinate == FVector2D(int32(-324 + (int32(fromCoordinate[0] - 'A') * 81)), int32(300 - (int32(fromCoordinate[1] - '1') * 81))) && OwningWidget->ChessPieces[j]->GetRenderOpacity() == 1) {
                ImageInCanvas->SetPosition(FVector2D(-324 + (int32(toCoordinate[0] - 'A') * 81), int32(300 - (int32(toCoordinate[1]-'1') * 81))));
                break;
            }
        }
    }
}

void UReplayMovesButton::ResetPiecesPosition() {
    for (int i = 0; i < 32; ++i) {
        OwningWidget->ChessPieces[i]->SetRenderOpacity(1);
        UCanvasPanelSlot* ImageInCanvas = Cast <UCanvasPanelSlot>(OwningWidget->ChessPieces[i]->Slot);
        switch (int8(i / 8)) {
        case 0:
            ImageInCanvas->SetPosition(FVector2D(int32(-324 + ((i % 8) * 81)), int32(300)));
            break;
        case 1:
            ImageInCanvas->SetPosition(FVector2D(int32(-324 + ((i % 8) * 81)), int32(219)));
            break;
        case 2:
            ImageInCanvas->SetPosition(FVector2D(int32(-324 + ((i % 8) * 81)), int32(-186)));
            break;
        case 3:
            ImageInCanvas->SetPosition(FVector2D(int32(-324 + ((i % 8) * 81)), int32(-267)));
            break;
        default:
            break;
        }
    }
}