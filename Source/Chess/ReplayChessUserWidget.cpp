#include "ReplayChessUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "HAL/FileManagerGeneric.h"
#include "ListButton.h"
#include "Engine/FontFace.h"

void UReplayChessUserWidget::ScanMatchRecords() {
    TArray<FString> output;
    output.Empty();
    FString Directory = FPaths::ProjectDir() / FString(TEXT("Content/GameplayResult/"));

    FCompositeFont MyCompFont = FCompositeFont(FName(TEXT("SegoeUISemiBold")), FPaths::ProjectDir() / "Content/Fonts/seguisb.ttf", EFontHinting::Default, EFontLoadingPolicy::LazyLoad);

    TSharedPtr<const FCompositeFont> MyInCompositeFont(new FCompositeFont(MyCompFont));

    FSlateFontInfo Font = FSlateFontInfo(MyInCompositeFont, 15);

    Font.LetterSpacing = 280;

    MatchScrollBox->ClearChildren();

    if (FPaths::DirectoryExists(Directory)) {
        FString path = Directory + "*.txt";
        FFileManagerGeneric::Get().FindFiles(output, *path, true, false);
        for (int i = 0; i < output.Num(); ++i) {
            UListButton* newButton = NewObject <UListButton>();
            newButton->Name = output[i];
            newButton->SetBackgroundColor(FLinearColor(1, 1, 1, 0));
            UTextBlock* newTextBlock = NewObject <UTextBlock>();
            FString textBlockString = output[i].Left(output[i].Len() - 4);
            for (int j = textBlockString.Len() - 1; j > 9; --j) {
                if (textBlockString[j] == '.') {
                    textBlockString[j] = ':';
                }
                else if (textBlockString[j] == '-') {
                    textBlockString[j] = ' ';
                }

                newTextBlock->SetFont(Font);
                newTextBlock->SetText(FText::FromString(textBlockString));
                newTextBlock->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
                newButton->OwningWidget = this;
                newButton->toReplayScrollBox = MovesScrollBox;
                newButton->AddChild(newTextBlock);
                MatchScrollBox->AddChild(newButton);
            }
        }
    }
}