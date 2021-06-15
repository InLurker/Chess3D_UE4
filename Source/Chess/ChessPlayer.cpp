#include "ChessPlayer.h"
#include "ChessBoard.h"
#include "ChessController.h"
#include "ChessPiece_Base.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ChessController.h"

// Sets default values
AChessPlayer::AChessPlayer() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Sets the root component, camera, and camera spring arm
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->SetRelativeRotation(FRotator(0.0f, 0.4f, 180.0f));
	CameraSpringArm->bDoCollisionTest = false;
	CameraSpringArm->TargetArmLength = 0.0f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 3.0f;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void AChessPlayer::BeginPlay() {
	Super::BeginPlay();
	//casts the controller to "Controller"

	Controller = Cast<AChessController>(GetController());
	ChessController = Cast<AChessController>(GetController());

}

// Called every frame
void AChessPlayer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (isPending) {
		if (CurrentSelectedPiece != nullptr) {
			if (mousePosition != FVector2D(NULL, NULL)) {
				float X, Y;
				ChessController->GetMousePosition(X, Y);
				FVector CurrentPieceLocation = CurrentSelectedPiece->GetActorLocation();
				FVector2D viewportSize;
				GEngine->GameViewport->GetViewportSize(viewportSize);
				int xOffset;
				int yOffset;
				if (isWhite()) {
					xOffset = (Y - mousePosition.Y) * (2200 / viewportSize.Y);
					yOffset = (X - mousePosition.X) * (2400 / viewportSize.X);
				}
				else {
					xOffset = (mousePosition.Y - Y) * (2200 / viewportSize.Y);
					yOffset = (mousePosition.X - X) * (2400 / viewportSize.X);
				}
				CurrentSelectedPiece->SetActorLocation(FVector(CurrentPieceLocation.X + xOffset, CurrentPieceLocation.Y - yOffset, 10));
				mousePosition.X = X;
				mousePosition.Y = Y;
			}
			else {
				ChessController = Cast<AChessController>(GetController());
				ChessController->GetMousePosition(mousePosition.X, mousePosition.Y);
			}
		}
	}
}
// Called to bind functionality to input
void AChessPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

int32 AChessPlayer::getScore() {
	return PlayerScore;
}

void AChessPlayer::addScore(int32 points) {
	PlayerScore += points;
}

// Returns player name
FText AChessPlayer::getName() {
	return PlayerName;
}

FVector AChessPlayer::GetCameraPanDirection() {
	// Variable to hold mouse position
	float MousePositionX = 0;
	float MousePositionY = 0;
	float CameraDirectionX = 0;
	float CameraDirectionY = 0;

	ChessController->GetMousePosition(MousePositionX, MousePositionY);
	if (MousePositionX == 0){
		CameraDirectionY = -1;
	}
	return FVector(CameraDirectionX, CameraDirectionY, 0);
}

bool AChessPlayer::isWhite() {
	//returns the color of this player
	return bIsWhite;
}

void AChessPlayer::setIsWhite(bool newValue) {
	//assigns the new value to bIsWhite
	bIsWhite = newValue;
}

void AChessPlayer::setCurrentPiece(AChessPiece_Base* newPiece) {
	CurrentSelectedPiece = newPiece;
}