#include "ChessController.h"
#include "tile.h"
#include "ChessBoard.h"
#include "ChessPlayer.h"
#include "ChessPointsWidget.h"
#include "WinningScreenWidget.h"
#include "ChessHUD.h"
#include "Misc/DateTime.h"
#include "Misc/FileHelper.h"
#include "ChessGameModeBase.h"
#include "ReplayChessUserWidget.h"
#include "WinningScreenWidget.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Components/TextBlock.h>
#include "Projection2D.h"

AChessController::AChessController() {
	DefaultMouseCursor = EMouseCursor::Default;
	bShowMouseCursor = true;						// Show mouse cursor
		// Set mouse cursor as default

	static ConstructorHelpers::FObjectFinder<UMaterial> Material (TEXT("Material'/Game/Materials/Highlights/Select_Highlight.Select_Highlight'"));
	if (Material.Object != NULL) {
		SelectedMaterial = (UMaterial*)Material.Object;
	}
	TArray <AActor*> FoundPlayers;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChessPlayer::StaticClass(), FoundPlayers);
	AChessPlayer* temp;
	for (int i = 0; i < FoundPlayers.Num(); ++i) {
		temp = Cast <AChessPlayer>(FoundPlayers[i]);
		if (temp != nullptr) {
			if (temp->isWhite())
				PlayerOne = temp;
			else
				PlayerTwo = temp;
		}
	}
	CurrentPlayer = PlayerOne;
	Possess(PlayerOne);
	FoundPlayers.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChessBoard::StaticClass(), FoundPlayers);
	if (FoundPlayers.Num() > 0)
		ChessBoard = Cast <AChessBoard>(FoundPlayers[0]);
}

void AChessController::BeginPlay() {
	Super::BeginPlay();
	HUD = Cast <AChessHUD>(GetHUD());
	TextFileDirectory = FPaths::ProjectDir() / (FString(TEXT("Content/GameplayResult/")) + FDateTime::Now().ToString() + FString(TEXT(".txt")));
	
}

void AChessController::SetupInputComponent() {
	Super::SetupInputComponent();

	//Binds key actions to functions
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AChessController::OnLeftMouseClick);
	InputComponent->BindAction("LeftClick", IE_Released, this, &AChessController::OnLeftMouseRelease);

	InputComponent->BindAction("RightClick", IE_Pressed, this, &AChessController::OnRightMouseClick);
}

void AChessController::OnLeftMouseClick() {
	if (this->SelectedPiece != nullptr) {
		this->SelectedPiece->SetDeselected();
	}
	Deselect();
	SelectPiece();
	if (SelectedPiece != nullptr) {
		if (SelectedPiece->isWhite() == CurrentPlayer->isWhite()) {
			isPending = true;
			PieceLocation = SelectedPiece->GetActorLocation();
			CurrentPlayer->isPending = true;
			CurrentPlayer->setCurrentPiece(SelectedPiece);
			CurrentMouseCursor = EMouseCursor::GrabHandClosed;
			SelectedPiece->setOverlap(true);
			SelectedPiece->StaticMesh->SetSimulatePhysics(false);
		}
	}
}

void AChessController::OnLeftMouseRelease() {
	FVector CurrentPieceLocation;
	if (SelectedPiece != nullptr)
		CurrentPieceLocation = SelectedPiece->GetActorLocation();

	if (CurrentPieceLocation.X >= 300 && CurrentPieceLocation.X <= 1900) {
		if (CurrentPieceLocation.Y >= -300 && CurrentPieceLocation.Y <= 1300) {
			int Row = round((1800 - CurrentPieceLocation.X) / 200);
			int Column = round((1200 - CurrentPieceLocation.Y) / 200);
			int index = (Row * 8) + Column;
			SelectedGrid = ChessBoard->TilesCollection[index];
			for (Atile* Grid : SelectableGrids) {
				if (SelectedGrid == Grid) {// Checks if the grid selected is selectable
					SelectedPiece->neverMove = false;
					CurrentPlayer->isPending = false;
					CurrentPlayer->setCurrentPiece(nullptr);
					isPending = false;
					isPending = false;
					SelectedPiece->setOverlap(false);
					MakeMove();
					Deselect();
					SelectableGrids.Empty(); // Empty previous records.
					EliminatePieces.Empty(); // Empty previous records.
					break;
				}
			}
		}
	}

	if (isPending == true && SelectedPiece != nullptr) {
		SelectedPiece->SetActorLocation(PieceLocation, false, nullptr, ETeleportType::TeleportPhysics);
		isPending = false;
		SelectedPiece->setOverlap(false);
	}
	
	CurrentPlayer->mousePosition.X = NULL;
	CurrentPlayer->mousePosition.Y = NULL;
	CurrentPlayer->setCurrentPiece(nullptr);
	CurrentMouseCursor = DefaultMouseCursor;
}

void AChessController::OnRightMouseClick() {
	Deselect();
	FHitResult RightClickResult(ForceInit); // Will hold hit result
	GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, true, RightClickResult); // Get hit result and assign it to TraceResult
	if (RightClickResult.GetActor() != nullptr) {
		SelectedGrid = Cast <Atile>(RightClickResult.GetActor());
		for (Atile* Grid : SelectableGrids) { 
			if (SelectedGrid == Grid) {// Checks if the grid selected is selectable
				SelectedPiece->setOverlap(false);
				SelectedPiece->neverMove = false;
				CurrentPlayer->isPending = false;
				isPending = false;
				MakeMove();
				CurrentPlayer->setCurrentPiece(nullptr);
			}
		}
	}
	SelectableGrids.Empty(); // Empty previous records.
	EliminatePieces.Empty(); // Empty previous records.
}

void AChessController::SelectPiece() {
	/* Detects clicked area */
	FHitResult TraceResult(ForceInit); // Will hold hit result
	GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, true, TraceResult); // Get hit result and assign it to TraceResult

	// If Hit Target was a an Actor.
	if (TraceResult.GetActor() != nullptr) {
		/* If selected actor is a Parent Actor */
		if (TraceResult.GetActor()->IsA(AChessPiece_Base::StaticClass())) {
			SelectedPiece = Cast<AChessPiece_Base>(TraceResult.GetActor()); // Cast actor to AChessPiece_base
			if (SelectedPiece != nullptr) { // Check if cast was successful 
				if (SelectedPiece->isWhite() == CurrentPlayer->isWhite()) {
					IsAnythingSelected = true;		// Set Checker variable to True
					SelectedPiece->SetSelected();
					HighlightSelectableGrids();		// Highlights Selectable Grids
					isPending = true;
					return;
				}
			}
		}
	}
	IsAnythingSelected = false;
}

void AChessController::HighlightSelectableGrids() {
	if (IsAnythingSelected == false)
		return;

	SelectableGrids.Empty(); // Empty previous records.
	EliminatePieces.Empty(); // Empty previous records.

	SelectedPiece->DetectSelectableGrids(&SelectableGrids);
	for (int i = 0; i < SelectableGrids.Num(); ++i) {
		SelectableGrids[i]->highlight();
	}
}

void AChessController::Deselect() {
	for (int32 index = 0; index < SelectableGrids.Num(); index++)
		SelectableGrids[index]->unhighlight();

	SelectedGrid = nullptr;
}

void AChessController::SwitchPlayer() {
	if (CurrentPlayer == PlayerTwo) {
		PreviousPlayer = PlayerTwo;
		CurrentPlayer = PlayerOne;
		Possess(PlayerOne);
	}
	else if (CurrentPlayer == PlayerOne) {
		PreviousPlayer = PlayerOne;
		CurrentPlayer = PlayerTwo;
		Possess(PlayerTwo);
	}
}

AChessPlayer* AChessController::GetCurrentPlayer(){
	return CurrentPlayer;
}

AChessPlayer* AChessController::GetPlayerOne() {
	return PlayerOne;
}

AChessPlayer* AChessController::GetPlayerTwo() {
	return PlayerTwo;
}

void AChessController::MakeMove() {
	bool take = false;
	if (SelectedGrid->isOccupied()) {
		take = true;
		if (CurrentPlayer == PlayerOne) {
			HUD->widgetPoint1->addScore(SelectedGrid->currentOccupyingPiece->getPiecePoint());
			PlayerOne->addScore(SelectedGrid->currentOccupyingPiece->getPiecePoint());
		}
		else if (CurrentPlayer == PlayerTwo) {
			HUD->widgetPoint2->addScore(SelectedGrid->currentOccupyingPiece->getPiecePoint());
			PlayerTwo->addScore(SelectedGrid->currentOccupyingPiece->getPiecePoint());
		}
		SelectedGrid->currentOccupyingPiece->Discard();
	}

	int32 Column = round((1800 - SelectedPiece->tileOccupied->GetActorLocation().X) / 200);
	int32 Row = round((1200 - SelectedPiece->tileOccupied->GetActorLocation().Y) / 200);
	
	FString fromCoordinate = "A";

	fromCoordinate[0] = (*fromCoordinate.GetCharArray().GetData()) + Row;

	fromCoordinate += FString::FromInt(Column+1);

	FString from = fromCoordinate;

	SelectedPiece->tileOccupied->unoccupy();

	SelectedGrid->occupy(SelectedPiece);

	Column = round((1800 - SelectedGrid->GetActorLocation().X) / 200);
	Row = round((1200 - SelectedGrid->GetActorLocation().Y) / 200);

	FString toCoordinate = "A";

	toCoordinate[0] = (*toCoordinate.GetCharArray().GetData()) + Row;

	toCoordinate += FString::FromInt(Column+1);

	FString to = toCoordinate;

	fromCoordinate += " " + toCoordinate;

	if (take) {
		fromCoordinate += "(take)";
	}
	HUD->projection2DWidget->update2DBoard(from, to, take);
	GameLog.Add(fromCoordinate);
	if (CurrentPlayer->getScore() >= 100 && !endGame) {
		CurrentPlayer->addScore(-100);
		if (CurrentPlayer == PlayerOne)
			HUD->widgetPoint1->addScore(-100);
		else if (CurrentPlayer == PlayerTwo)
			HUD->widgetPoint2->addScore(-100);
		HUD->showWinningScreen();
		HUD->winningScreen->Ratio->SetText(FText::FromString(FString::FromInt(PlayerOne->getScore()) + ":" + FString::FromInt(PlayerTwo->getScore())));
		if (CurrentPlayer == PlayerOne)
			HUD->winningScreen->SetWinner("Player 1");
		else
			HUD->winningScreen->SetWinner("Player 2");
		GameLog.Add(FString::FromInt(PlayerOne->getScore()) + ":" + FString::FromInt(PlayerTwo->getScore()));
		FFileHelper::SaveStringArrayToFile(GameLog, *TextFileDirectory, FFileHelper::EEncodingOptions::ForceUTF8);
		endGame = true;
	}
	else {
		Deselect();
		SwitchPlayer(); // Switch player 

		SelectedPiece = nullptr;
	}
}

bool AChessController::getPending() {
	return isPending;
}