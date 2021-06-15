#include "ListButton.h"
#include "Components/ScrollBox.h"
#include "HAL/FileManagerGeneric.h"
#include "ReplayMovesButton.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "ReplayChessUserWidget.h"

UListButton::UListButton() {
    OnClicked.AddDynamic(this, &UListButton::OnClick);
}

void UListButton::OnClick() {
    ResetPiecesPosition();

    TArray<FString> output;

    FString Directory = FPaths::ProjectDir() / FString(TEXT("Content/GameplayResult/")) + Name;

    FFileHelper::LoadFileToStringArray(output, *Directory);

    FCompositeFont MyCompFont = FCompositeFont(FName(TEXT("SegoeUISemiBold")), FPaths::ProjectDir() + "Content/Fonts/seguisb.ttf", EFontHinting::Default, EFontLoadingPolicy::LazyLoad);

    TSharedPtr<const FCompositeFont> MyInCompositeFont(new FCompositeFont(MyCompFont));

    FSlateFontInfo Font = FSlateFontInfo(MyInCompositeFont, 15);

    Font.LetterSpacing = 280;

    toReplayScrollBox->ClearChildren();

    if (output.Num() > 0) {
        for (int i = 0; i < output.Num()-1; ++i) {
            UReplayMovesButton* newButton = NewObject <UReplayMovesButton> ();
            if (i % 2 == 0)
                newButton->SetBackgroundColor(FLinearColor(1, 1, 1, 0.2));
            else
                newButton->SetBackgroundColor(FLinearColor(0, 0, 0, 0.2));
            UTextBlock* newTextBlock = NewObject <UTextBlock>();
            newTextBlock->SetText(FText::FromString(output[i].Left(3) + "to " + output[i].Right(output[i].Len() - 3)));
            newButton->From = output[i].Left(2);
            newButton->To = output[i].Right(output[i].Len() - 3).Left(2);
            if (output[i].Len() > 5) {
                if (output[i].Right(6) == "(take)")
                    newButton->take = true;
            }
            else
                newButton->take = false;
            newButton->index = i;
            newButton->OwningWidget = OwningWidget;
            newTextBlock->SetFont(Font);
            newButton->AddChild(newTextBlock);
            toReplayScrollBox->AddChild(newButton);
        }
        OwningWidget->Ratio->SetText(FText::FromString(output[output.Num() - 1]));
    }
}
void UListButton::ResetPiecesPosition() {
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