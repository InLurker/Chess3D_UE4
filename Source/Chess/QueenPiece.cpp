#include "QueenPiece.h"
#include "ChessBoard.h"

// Default Constructor: Inherit ChessPiece_Base's constructor
AQueenPiece::AQueenPiece() : AChessPiece_Base() {
	// Finds the mesh of queen asset
	static ConstructorHelpers::FObjectFinder<UStaticMesh> QueenMesh(TEXT("StaticMesh'/Game/Meshes/Queen.Queen'"));

	// Sets the asset to the staticmesh
	if (QueenMesh.Succeeded()) {
		StaticMesh->SetStaticMesh(QueenMesh.Object);
		StaticMesh->SetWorldScale3D(FVector(0.1, 0.1, 0.1));
		RootComponent = StaticMesh;
	}
}

void AQueenPiece::DetectSelectableGrids(TArray<Atile*>* SelectableGrids) {
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

	//MOVESETS
	//Checks for all valid moves possible

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
	//Scan up
	for (int i = (verticalPosition * 8) + horizontalPosition + 8; i < 64; i += 8) {
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
	}

	//Scan down
	for (int i = (verticalPosition * 8) + horizontalPosition - 8; i >= 0; i -= 8) {
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
	}

	//Scan left
		//exit if went out of scope (left border)
	for (int i = (verticalPosition * 8) + horizontalPosition - 1; (i - (verticalPosition * 8)) >= 0; --i) {
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
	}

	//Scan right
		//exit if went out of scope (right border)
	for (int i = (verticalPosition * 8) + horizontalPosition + 1; (i - (verticalPosition * 8)) < 8; ++i) {
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
	}
}

int32 AQueenPiece::getPiecePoint()
{
	return int32(9);
}