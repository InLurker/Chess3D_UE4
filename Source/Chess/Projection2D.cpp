#include "Projection2D.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"

void UProjection2D::update2DBoard(const FString from, const FString to, bool take) {
	if (take) {
		for (int j = 0; j < 32; ++j) {
			FVector2D coordinate = (Cast <UCanvasPanelSlot>(Pieces2D[j]->Slot))->GetPosition();
			if (coordinate == FVector2D(int32(-390 + (int32(to[0] - 'A') * 40)), int32(450 - (int32(to[1] - '1') * 40))) && Pieces2D[j]->GetRenderOpacity() == 1) {
				Pieces2D[j]->SetRenderOpacity(0);
				break;
			}
		}
	}
	for (int j = 0; j < 32; ++j) {
		UCanvasPanelSlot* ImageInCanvas = Cast <UCanvasPanelSlot>(Pieces2D[j]->Slot);
		FVector2D coordinate = ImageInCanvas->GetPosition();
		if (coordinate == FVector2D(int32(-390 + (int32(from[0] - 'A') * 40)), int32(450 - (int32(from[1] - '1') * 40))) && Pieces2D[j]->GetRenderOpacity() == 1) {
			ImageInCanvas->SetPosition(FVector2D(-390 + (int32(to[0] - 'A') * 40), int32(450 - (int32(to[1] - '1') * 40))));
			break;
		}
	}
}

void UProjection2D::reset2DBoard() {
    for (int i = 0; i < 32; ++i) {
        Pieces2D[i]->SetRenderOpacity(1);
        UCanvasPanelSlot* ImageInCanvas = Cast <UCanvasPanelSlot>(Pieces2D[i]->Slot);
        switch (int8(i / 8)) {
        case 0:
            ImageInCanvas->SetPosition(FVector2D(int32(-390 + ((i % 8) * 40)), int32(450)));
            break;
        case 1:
            ImageInCanvas->SetPosition(FVector2D(int32(-390 + ((i % 8) * 40)), int32(410)));
            break;
        case 2:
            ImageInCanvas->SetPosition(FVector2D(int32(-390 + ((i % 8) * 40)), int32(210)));
            break;
        case 3:
            ImageInCanvas->SetPosition(FVector2D(int32(-390 + ((i % 8) * 40)), int32(170)));
            break;
        default:
            break;
        }
    }
}
