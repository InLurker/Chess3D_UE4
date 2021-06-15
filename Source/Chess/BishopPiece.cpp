#include "BishopPiece.h"
#include "ChessBoard.h"

// Default Constructor: Inherit ChessPiece_Base's constructor
ABishopPiece::ABishopPiece() : AChessPiece_Base() {
	// Finds the mesh of bishop asset
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BishopMesh(TEXT("StaticMesh'/Game/Meshes/Bishop.Bishop'"));

	// Sets the asset to the staticmesh
	if (BishopMesh.Succeeded()) {
		StaticMesh->SetStaticMesh(BishopMesh.Object);
		StaticMesh->SetWorldScale3D(FVector(0.1, 0.1, 0.1));
		RootComponent = StaticMesh;
	}
}

void ABishopPiece::DetectSelectableGrids(TArray<Atile*>* SelectableGrids) {
	//initialized to -1
	int verticalPosition = -1;
	int horizontalPosition = -1;

	//finds the index of the tileOccupied
	for (int i = 0; i < 64; ++i) {
		if (HostBoard->TilesCollection[i] == this->tileOccupied) {
			horizontalPosition = i % 8;
			verticalPosition = i / 8;
			break;
		}
	}

	//if failed to find index, return
	if (verticalPosition == -1 || horizontalPosition == -1)
		return;

	//MOVESETS
	//Checks for all valid moves possible

	//Scan diagonal spaces for possible movements
	//Scan top-left
	if (horizontalPosition > 0 && verticalPosition < 7) {
		for (int i = (verticalPosition * 8) + horizontalPosition + 7; i < 64; i += 7) {
			if (!(HostBoard->TilesCollection[i]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[i]);
			}
			else {
				//when the chess tile is occupied
				//check whether the color of the piece is the same as the one blocking the path
				if (HostBoard->TilesCollection[i]->currentOccupyingPiece->isWhite() != this->isWhite())
					SelectableGrids->Add(HostBoard->TilesCollection[i]);
				break;
			}
			if (i % 8 == 0) {
				//exit when out of bounds (left border)
				break;
			}
		}
	}
	//Scan top-right
	if (horizontalPosition < 7 && verticalPosition < 7) {
		for (int i = (verticalPosition * 8) + horizontalPosition + 9; i < 64; i += 9) {
			if (!(HostBoard->TilesCollection[i]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[i]);
			}
			else {
				//when the chess tile is occupied
				//check whether the color of the piece is the same as the one blocking the path
				if (HostBoard->TilesCollection[i]->currentOccupyingPiece->isWhite() != this->isWhite())
					SelectableGrids->Add(HostBoard->TilesCollection[i]);
				break;
			}

			if (i % 8 == 7) {
				//exit when out of bounds (left border)
				break;
			}
		}
	}
	//Scan bottom-left
	if (horizontalPosition > 0 && verticalPosition > 0) {
		for (int i = (verticalPosition * 8) + horizontalPosition - 9; i >= 0; i -= 9) {
			if (!(HostBoard->TilesCollection[i]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[i]);
			}
			else {
				//when the chess tile is occupied
				//check whether the color of the piece is the same as the one blocking the path
				if (HostBoard->TilesCollection[i]->currentOccupyingPiece->isWhite() != this->isWhite())
					SelectableGrids->Add(HostBoard->TilesCollection[i]);
				break;
			}

			if (i % 8 == 0) {
				//exit when out of bounds (left border)
				break;
			}
		}
	}
	//Scan bottom-right
	if (horizontalPosition < 7 && verticalPosition > 0) {
		for (int i = (verticalPosition * 8) + horizontalPosition - 7; i >= 0; i -= 7) {
			if (!(HostBoard->TilesCollection[i]->isOccupied())) {
				//when the chess tiles are not occupied
				SelectableGrids->Add(HostBoard->TilesCollection[i]);
			}
			else {
				//when the chess tile is occupied
				//check whether the color of the piece is the same as the one blocking the path
				if (HostBoard->TilesCollection[i]->currentOccupyingPiece->isWhite() != this->isWhite())
					SelectableGrids->Add(HostBoard->TilesCollection[i]);
				break;
			}

			if (i % 8 == 7) {
				//exit when out of bounds (left border)
				break;
			}
		}
	}
}

int32 ABishopPiece::getPiecePoint(){
	return int32(3);
}
