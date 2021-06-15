#include "PawnPiece.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ChessBoard.h"

// Default Constructor: Inherit ChessPiece_Base's constructor
APawnPiece::APawnPiece() : AChessPiece_Base() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Finds the mesh of pawn asset
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PawnMesh(TEXT("StaticMesh'/Game/Meshes/Pawn.Pawn'"));

	// Sets the asset to the staticmesh
	if (PawnMesh.Succeeded()) {
		StaticMesh->SetStaticMesh(PawnMesh.Object);
		StaticMesh->SetWorldScale3D(FVector(0.1, 0.1, 0.1));
		RootComponent = StaticMesh;
	}
}

void APawnPiece::DetectSelectableGrids(TArray<Atile*>* SelectableGrids) {
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

	if (isWhite()) {
		//if the piece is not on the edge of the board
		if (verticalPosition < 7) {
			//if the tile in front is not occupied, then add it to selectable grid
			if (!(HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition + 8]->isOccupied())) {
				SelectableGrids->Add(HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition + 8]);

				// If first time moving, add the second tile in front of it into the selectable grid
				if (neverMove) {
					if (!(HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition + 16]->isOccupied()))
						SelectableGrids->Add(HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition + 16]);
				}
			}
			if (horizontalPosition > 0) {
				//if the tile in front-left is occupied, then add it to selectable grid
				if (HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition + 7]->isOccupied()) {
					if (!HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition + 7]->currentOccupyingPiece->isWhite()) {
						SelectableGrids->Add(HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition + 7]);
					}
				}
			}
			if (horizontalPosition < 7) {
				//if the tile in front-right is occupied, then add it to selectable grid
				if (HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition + 9]->isOccupied()) {
					if (!HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition + 9]->currentOccupyingPiece->isWhite()) {
						SelectableGrids->Add(HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition + 9]);
					}
				}
			}
		}
	}
	else {
		//if the piece is not on the edge of the board
		if (verticalPosition > 0) {
			//if the tile in front is not occupied, then add it to selectable grid
			if (!(HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition - 8]->isOccupied())) {
				SelectableGrids->Add(HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition - 8]);

				// If first time moving, add the second tile in front of it into the selectable grid
				if (neverMove) {
					if (!(HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition - 16]->isOccupied()))
						SelectableGrids->Add(HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition - 16]);
				}
			}
			//if piece is not on the edge
			if (horizontalPosition < 7) {
				//if the tile in front-left is occupied, then add it to selectable grid
				if (HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition - 7]->isOccupied()) {
					if (HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition - 7]->currentOccupyingPiece->isWhite()) {
						SelectableGrids->Add(HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition - 7]);
					}
				}
			}
			if (horizontalPosition > 0) {
				//if the tile in front-right is occupied, then add it to selectable grid
				if (HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition - 9]->isOccupied()) {
					if (HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition - 9]->currentOccupyingPiece->isWhite()) {
						SelectableGrids->Add(HostBoard->TilesCollection[(verticalPosition * 8) + horizontalPosition - 9]);
					}
				}
			}
		}
	}
}

int32 APawnPiece::getPiecePoint() {
	return int32(1);
}
