#include "KnightPiece.h"
#include "ChessBoard.h"

// Default Constructor: Inherit ChessPiece_Base's constructor
AKnightPiece::AKnightPiece() : AChessPiece_Base() {
	// Finds the mesh of knight asset
	static ConstructorHelpers::FObjectFinder<UStaticMesh> KnightMesh (TEXT("StaticMesh'/Game/Meshes/Knight.Knight'"));

	// Sets the asset to the staticmesh
	if (KnightMesh.Succeeded()) {
		StaticMesh->SetStaticMesh(KnightMesh.Object);
		StaticMesh->SetWorldScale3D(FVector(0.1, 0.1, 0.1));
		RootComponent = StaticMesh;
	}
}

void AKnightPiece::DetectSelectableGrids(TArray<Atile*>* SelectableGrids) {
	//initialized to -1
	int tilePosition = -1;
	int verticalPosition = -1;
	int horizontalPosition = -1;

	//finds the index of the tileOccupied
	for (int i = 0; i < 64; ++i) {
		if (HostBoard->TilesCollection[i] == this->tileOccupied) {
			horizontalPosition = i % 8;
			verticalPosition = i / 8;
			tilePosition = i;
			break;
		}
	}

	//if failed to find index, return
	if (tilePosition == -1 || verticalPosition == -1 || horizontalPosition == -1)
		return;

	//MOVESETS
	//Checks for all valid moves possible
	if (horizontalPosition > 1) {
		if (verticalPosition < 7) {
			//<————
			//    |
			if (!(HostBoard->TilesCollection[tilePosition + 6]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 6]);
			}
			else if (HostBoard->TilesCollection[tilePosition + 6]->currentOccupyingPiece->isWhite() != this->isWhite()) {
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 6]);
			}
		}
		if (verticalPosition > 0) {
			//    |
			//<————
			if (!(HostBoard->TilesCollection[tilePosition - 10]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 10]);
			}
			else if (HostBoard->TilesCollection[tilePosition - 10]->currentOccupyingPiece->isWhite() != this->isWhite()) {
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 10]);
			}
		}
	}

	if (horizontalPosition > 0) {
		if (verticalPosition < 6) {
			//<——
			//  |
			//  |
			if (!(HostBoard->TilesCollection[tilePosition + 15]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 15]);
			}
			else if (HostBoard->TilesCollection[tilePosition + 15]->currentOccupyingPiece->isWhite() != this->isWhite()) {
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 15]);
			}
		}
		if (verticalPosition > 1) {
			//  |
			//  |
			//<——
			if (!(HostBoard->TilesCollection[tilePosition - 17]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 17]);
			}
			else if (HostBoard->TilesCollection[tilePosition - 17]->currentOccupyingPiece->isWhite() != this->isWhite()) {
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 17]);
			}
		}
	}

	if (horizontalPosition < 6) {
		if (verticalPosition < 7) {
			//————>
			//|
			if (!(HostBoard->TilesCollection[tilePosition + 10]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 10]);
			}
			else if (HostBoard->TilesCollection[tilePosition + 10]->currentOccupyingPiece->isWhite() != this->isWhite()) {
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 10]);
			}
		}
		if (verticalPosition > 0) {
			//|
			//————>
			if (!(HostBoard->TilesCollection[tilePosition - 6]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 6]);
			}
			else if (HostBoard->TilesCollection[tilePosition - 6]->currentOccupyingPiece->isWhite() != this->isWhite()) {
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 6]);
			}
		}
	}

	if (horizontalPosition < 7) {
		if (verticalPosition < 6) {
			//——>
			//|
			//|
			if (!(HostBoard->TilesCollection[tilePosition + 17]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 17]);
			}
			else if (HostBoard->TilesCollection[tilePosition + 17]->currentOccupyingPiece->isWhite() != this->isWhite()) {
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 17]);
			}
		}
		if (verticalPosition > 1) {
			//|
			//|
			//——>
			if (!(HostBoard->TilesCollection[tilePosition - 15]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 15]);
			}
			else if (HostBoard->TilesCollection[tilePosition - 15]->currentOccupyingPiece->isWhite() != this->isWhite()) {
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 15]);
			}
		}
	}
}

int32 AKnightPiece::getPiecePoint()
{
	return int32(3);
}
