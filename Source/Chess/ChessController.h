#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChessPiece_Base.h"
#include "ChessController.generated.h"

//forward declarations
class AChessPlayer;
class AChessBoard;
class Atile;
UCLASS()
class CHESS_API AChessController : public APlayerController {
	GENERATED_BODY()

private:
	// Pointer to the chessboard
	UPROPERTY(EditAnywhere)
		AChessBoard* ChessBoard;

	// Pointer to the first player
	UPROPERTY(EditAnyWhere)
		AChessPlayer* PlayerOne;

	// Pointer to the second player
	UPROPERTY(EditAnyWhere)
		AChessPlayer* PlayerTwo;

	// Pointer array to store all the tiles valid to move into
	TArray<Atile*> SelectableGrids;

	// Pointer array to store all the pieces that might get eliminated
	TArray<AChessPiece_Base*> EliminatePieces;

	// bool to check whether the left click is being held or not
	bool isPending = false;

	// bool to check whether anything is selected or not
	bool IsAnythingSelected = false;

	// Temporarily store a piece's location
	FVector PieceLocation;

	// Stores the game's directory path
	FString TextFileDirectory;

	// Stores the moves made by the players
	TArray<FString> GameLog;

	// Function to bind with the left click input
	void OnLeftMouseClick();

	// Function to bind when left click is released
	void OnLeftMouseRelease();

	// Function to bind with the right click input
	void OnRightMouseClick();

	// Function to select a chess piece
	void SelectPiece();

	// Function to highlight the selectable grids
	void HighlightSelectableGrids();

	// Funtion to deselect the selected chess piece
	void Deselect();

	// Function to switch between the players
	void SwitchPlayer();

	// Function to execute a move
	void MakeMove();

	// Function to set the key bindings
	virtual void SetupInputComponent() override;

	// Pointer to the chess HUD
	class AChessHUD* HUD;

public:
	// To set that the game is over
	bool endGame = false;

	AChessController();

	virtual void BeginPlay() override;

	// Returns the bool isPending
	bool getPending();

	// Returns the address of current player
	AChessPlayer* GetCurrentPlayer();

	AChessPlayer* GetPlayerOne();

	AChessPlayer* GetPlayerTwo();

	// Pointer to the chess piece selected
	AChessPiece_Base* SelectedPiece;

	// Pointer to the tile selected
	Atile* SelectedGrid;

	// Pointer to material when a piece is selected
	UPROPERTY(VisibleAnyWhere)
		class UMaterial* SelectedMaterial;

	// Pointer to players
	AChessPlayer* PreviousPlayer;
	AChessPlayer* CurrentPlayer = PlayerOne;

	void ClearRecords();
};