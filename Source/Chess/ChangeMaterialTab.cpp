#include "ChangeMaterialTab.h"
#include "Animation/WidgetAnimation.h"
#include "UMG/Public/Components/Button.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "ChessBoard.h"
#include "tile.h"
#include "ChessPiece_Base.h"
#include "Engine/StaticMeshActor.h"

void UChangeMaterialTab::NativeConstruct() {
	OpenButton->OnClicked.AddDynamic(this, &UChangeMaterialTab::OpenCloseAnimation);

	BlackWhiteButton->OnClicked.AddDynamic(this, &UChangeMaterialTab::SwitchToDefault);
	GlassButton->OnClicked.AddDynamic(this, &UChangeMaterialTab::SwitchToGlass);
	WoodButton->OnClicked.AddDynamic(this, &UChangeMaterialTab::SwitchToWood);
	MetallicButton->OnClicked.AddDynamic(this, &UChangeMaterialTab::SwitchToMetal);
	To24KButton->OnClicked.AddDynamic(this, &UChangeMaterialTab::SwitchTo24K);
	AcrylicButton->OnClicked.AddDynamic(this, &UChangeMaterialTab::SwitchToAcrylic);


	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChessBoard::StaticClass(), FoundActors);
	ChessBoard = Cast <AChessBoard> (FoundActors[0]);
}

void UChangeMaterialTab::OpenCloseAnimation() {
	if (open) {
		PlayAnimation(CloseTab);
		open = false;
	}
	else { 
		PlayAnimation(OpenTab);
		open = true;
	}
}

void UChangeMaterialTab::SwitchToDefault() {
	SwitchMaterial(ChessBoard->WhitePieceMaterial,
		ChessBoard->BlackPieceMaterial,
		ChessBoard->WhiteTileMaterial,
		ChessBoard->BlackTileMaterial);
}

void UChangeMaterialTab::SwitchToGlass() {
	(Cast <AStaticMeshActor>(ChessBoard->ChessBorders[0]))->GetStaticMeshComponent()->SetMaterial(0, ChessBoard->BlackTileGlassMaterial);

	(Cast <AStaticMeshActor>(ChessBoard->ChessBorders[1]))->GetStaticMeshComponent()->SetMaterial(0, ChessBoard->WhiteTileGlassMaterial);
	SwitchMaterial(ChessBoard->WhitePieceGlassMaterial,
		ChessBoard->BlackPieceGlassMaterial, 
		ChessBoard->WhiteTileGlassMaterial,
		ChessBoard->BlackTileGlassMaterial);
}

void UChangeMaterialTab::SwitchToWood() {
	SwitchMaterial(ChessBoard->WhitePieceWoodenMaterial,
		ChessBoard->BlackPieceWoodenMaterial,
		ChessBoard->WhiteTileWoodenMaterial,
		ChessBoard->BlackTileWoodenMaterial);

	(Cast <AStaticMeshActor>(ChessBoard->ChessBorders[0]))->GetStaticMeshComponent()->SetMaterial(0, ChessBoard->BlackTileWoodenMaterial);

	(Cast <AStaticMeshActor>(ChessBoard->ChessBorders[1]))->GetStaticMeshComponent()->SetMaterial(0, ChessBoard->WhitePieceWoodenMaterial);
}

void UChangeMaterialTab::SwitchToMetal() {
	SwitchMaterial(ChessBoard->WhitePieceMetallicMaterial,
		ChessBoard->BlackPieceMetallicMaterial,
		ChessBoard->WhiteTileMetallicMaterial,
		ChessBoard->BlackTileMetallicMaterial);

	(Cast <AStaticMeshActor>(ChessBoard->ChessBorders[0]))->GetStaticMeshComponent()->SetMaterial(0, ChessBoard->BlackPieceMetallicMaterial);

	(Cast <AStaticMeshActor>(ChessBoard->ChessBorders[1]))->GetStaticMeshComponent()->SetMaterial(0, ChessBoard->BlackTileMetallicMaterial);
}

void UChangeMaterialTab::SwitchTo24K() {
	SwitchMaterial(ChessBoard->WhitePiece24KMaterial,
		ChessBoard->BlackPiece24KMaterial,
		ChessBoard->WhiteTile24KMaterial,
		ChessBoard->BlackTile24KMaterial);

	(Cast <AStaticMeshActor>(ChessBoard->ChessBorders[0]))->GetStaticMeshComponent()->SetMaterial(0, ChessBoard->BlackTile24KMaterial);

	(Cast <AStaticMeshActor>(ChessBoard->ChessBorders[1]))->GetStaticMeshComponent()->SetMaterial(0, ChessBoard->WhiteTile24KMaterial);
}

void UChangeMaterialTab::SwitchToAcrylic() {
	for (Atile* tile : ChessBoard->TilesCollection) {
		tile->switchMaterial(ChessBoard->WhiteTileAcrylicMaterial, ChessBoard->BlackTileAcrylicMaterial);
	}
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChessPiece_Base::StaticClass(), FoundActors);
	for (AActor* piece : FoundActors) {
		(Cast <AChessPiece_Base>(piece))->SwitchMaterial(ChessBoard->WhitePieceAcrylicMaterial, ChessBoard->BlackPieceAcrylicMaterial);
	}
	(Cast <AStaticMeshActor>(ChessBoard->ChessBorders[0]))->GetStaticMeshComponent()->SetMaterial(0, ChessBoard->BlackTileAcrylicMaterial);

	(Cast <AStaticMeshActor>(ChessBoard->ChessBorders[1]))->GetStaticMeshComponent()->SetMaterial(0, ChessBoard->WhiteTileAcrylicMaterial);
}

void UChangeMaterialTab::SwitchMaterial(UMaterial* LightP, UMaterial* DarkP, UMaterial* LightT, UMaterial* DarkT) {
	for (Atile* tile : ChessBoard->TilesCollection) {
		tile->switchMaterial(LightT, DarkT);
	}
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChessPiece_Base::StaticClass(), FoundActors);
	for (AActor* piece : FoundActors) {
		(Cast <AChessPiece_Base>(piece))->SwitchMaterial(LightP, DarkP);
	}
	(Cast <AStaticMeshActor>(ChessBoard->ChessBorders[0]))->GetStaticMeshComponent()->SetMaterial(0, DarkP);

	(Cast <AStaticMeshActor>(ChessBoard->ChessBorders[1]))->GetStaticMeshComponent()->SetMaterial(0, LightP);
}

void UChangeMaterialTab::SwitchMaterial(UMaterialInstance* LightP, UMaterialInstance* DarkP, UMaterialInstance* LightT, UMaterialInstance* DarkT) {
	for (Atile* tile : ChessBoard->TilesCollection) {
		tile->switchMaterial(LightT, DarkT);
	}
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChessPiece_Base::StaticClass(), FoundActors);
	for (AActor* piece : FoundActors) {
		(Cast <AChessPiece_Base>(piece))->SwitchMaterial(LightP, DarkP);
	}
}