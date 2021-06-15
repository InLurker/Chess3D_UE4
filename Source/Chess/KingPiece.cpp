#include "KingPiece.h"
#include "ChessBoard.h"

AKingPiece::AKingPiece() : AChessPiece_Base() {
	// Finds the mesh of king asset
	static ConstructorHelpers::FObjectFinder<UStaticMesh> KingMesh(TEXT("StaticMesh'/Game/Meshes/King.King'"));

	// Sets the asset to the staticmesh
	if (KingMesh.Succeeded()) {
		StaticMesh->SetStaticMesh(KingMesh.Object);
		StaticMesh->SetWorldScale3D(FVector(0.1, 0.1, 0.1));
		RootComponent = StaticMesh;
	}
}

void AKingPiece::DetectSelectableGrids(TArray<Atile*>* SelectableGrids) {
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

	// MOVESETS
	// Checks for all valid moves possible

	//check up
	if (verticalPosition < 7) {
		if (!(HostBoard->TilesCollection[tilePosition + 8]->isOccupied())) {
			//when the chess tiles are not occupied
			SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 8]);
		}
		else if (HostBoard->TilesCollection[tilePosition + 8]->currentOccupyingPiece->isWhite() != this->isWhite()) {
			SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 8]);
		}

		//check topleft
		if (horizontalPosition > 0) {
			if (!(HostBoard->TilesCollection[tilePosition + 7]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 7]);
			}
			else if (HostBoard->TilesCollection[tilePosition + 7]->currentOccupyingPiece->isWhite() != this->isWhite()) {
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 7]);
			}
		}

		//check topright
		if (horizontalPosition < 7) {
			if (!(HostBoard->TilesCollection[tilePosition + 9]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 9]);
			}
			else if (HostBoard->TilesCollection[tilePosition + 9]->currentOccupyingPiece->isWhite() != this->isWhite()) {
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 9]);
			}
		}
	}

	//check down
	if (verticalPosition > 0) {
		if (!(HostBoard->TilesCollection[tilePosition - 8]->isOccupied())) {
			//when the chess tiles are not occupied
			SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 8]);
		}
		else if (HostBoard->TilesCollection[tilePosition - 8]->currentOccupyingPiece->isWhite() != this->isWhite()) {
			SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 8]);
		}

		//check bottom left
		if (horizontalPosition > 0) {
			if (!(HostBoard->TilesCollection[tilePosition - 9]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 9]);
			}
			else if (HostBoard->TilesCollection[tilePosition - 9]->currentOccupyingPiece->isWhite() != this->isWhite()) {
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 9]);
			}
		}

		//check bottom right
		if (horizontalPosition < 7) {
			if (!(HostBoard->TilesCollection[tilePosition - 7]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 7]);
			}
			else if (HostBoard->TilesCollection[tilePosition - 7]->currentOccupyingPiece->isWhite() != this->isWhite()) {
				SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 7]);
			}
		}
	}

	//check left
	if (horizontalPosition > 0) {
		if (!(HostBoard->TilesCollection[tilePosition - 1]->isOccupied())) {
			//when the chess tiles are not occupied
			SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 1]);
		}
		else if (HostBoard->TilesCollection[tilePosition - 1]->currentOccupyingPiece->isWhite() != this->isWhite()) {
			SelectableGrids->Add(HostBoard->TilesCollection[tilePosition - 1]);
		}
	}

	//check right
	if (horizontalPosition < 7) {
		if (!(HostBoard->TilesCollection[tilePosition + 1]->isOccupied())) {
			//when the chess tiles are not occupied
			SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 1]);
		}
		else if (HostBoard->TilesCollection[tilePosition + 1]->currentOccupyingPiece->isWhite() != this->isWhite()) {
			SelectableGrids->Add(HostBoard->TilesCollection[tilePosition + 1]);
		}
	}
}

int32 AKingPiece::getPiecePoint()
{
	return int32(100);
}
