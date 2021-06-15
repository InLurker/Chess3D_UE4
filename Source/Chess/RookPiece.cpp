#include "RookPiece.h"
#include "ChessBoard.h"

// Default Constructor: Inherit ChessPiece_Base's constructor
ARookPiece::ARookPiece() : AChessPiece_Base() {
	// Finds the mesh of rook asset
	static ConstructorHelpers::FObjectFinder<UStaticMesh> RookMesh(TEXT("StaticMesh'/Game/Meshes/Rook.Rook'"));
	
	// Sets the asset to the staticmesh
	if (RookMesh.Succeeded()) {
		StaticMesh->SetStaticMesh(RookMesh.Object);
		StaticMesh->SetWorldScale3D(FVector(0.1, 0.1, 0.1));
		RootComponent = StaticMesh;
	}
}

void ARookPiece::DetectSelectableGrids(TArray<Atile*>* SelectableGrids) {
	//initialized to -1
	int verticalPosition = -1;
	int horizontalPosition = -1;
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
	
	//Scan vertical spaces for possible movements

	//MOVESETS
	//Checks for all valid moves possible

	//Scan up
	for (int i = (verticalPosition * 8) + horizontalPosition + 8; i < 64; i+=8) {
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

int32 ARookPiece::getPiecePoint()
{
	return int32(5);
}
