#include "ChessPiece_Base.h"
#include "ChessBoard.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AChessPiece_Base::AChessPiece_Base() {
	// Set to True to call Tick() every frame
	// Set to False for better performance
	PrimaryActorTick.bCanEverTick = false;

	// Creates static mesh and assign it as its root
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetCollisionProfileName(TEXT("ChessPiece"));	// Sets Collision
	StaticMesh->SetSimulatePhysics(false);						// Sets Physics


	// Sets the WhiteMaterial (The material for the white chess pieces)
	static ConstructorHelpers::FObjectFinder<UMaterial> GetWhiteMaterial(TEXT("Material'/Game/Materials/BnW(Default)/Piece_W.Piece_W'"));
	if (GetWhiteMaterial.Succeeded())
		WhiteMaterial = GetWhiteMaterial.Object;

	// Sets the BlackMaterial (The material for the black chess pieces)
	static ConstructorHelpers::FObjectFinder<UMaterial> GetBlackMaterial(TEXT("Material'/Game/Materials/BnW(Default)/Piece_B.Piece_B'"));
	if (GetBlackMaterial.Succeeded())
		BlackMaterial = GetBlackMaterial.Object;

	// Sets the Selection Highlight's Material
	static ConstructorHelpers::FObjectFinder<UMaterial> GetSelectedMaterial(TEXT("Material'/Game/Materials/Highlights/Select_Highlight.Select_Highlight'"));
	if (GetSelectedMaterial.Succeeded())
		SelectedMaterial = GetSelectedMaterial.Object;

	// Set the to-be Eliminated Material
	static ConstructorHelpers::FObjectFinder<UMaterial> GetEliminateMaterial(TEXT("Material'/Game/Materials/Highlights/Eliminate_Highlight.Eliminate_Highlight'"));
	if (GetEliminateMaterial.Succeeded())
		EliminateMaterial = GetEliminateMaterial.Object;
}

// Called when the game starts or when spawned
void AChessPiece_Base::BeginPlay(){
	Super::BeginPlay();
	OriginalPosition = GetActorLocation();
	OriginalTile = tileOccupied;
}

// Called every frame
void AChessPiece_Base::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

// Call when a chess piece is selected, and changes the material of the object
void AChessPiece_Base::SetSelected(){
	StaticMesh->SetMaterial(0, SelectedMaterial);
}

// Change the material of a chess piece if it is about to get eliminated
void AChessPiece_Base::SetEliminateMaterial(){
	StaticMesh->SetMaterial(0, EliminateMaterial);
}

// When a chess piece is deselected, change its material back to its original state
void AChessPiece_Base::SetDeselected(){
	if (bIsWhite)
		StaticMesh->SetMaterial(0, WhiteMaterial);
	else
		StaticMesh->SetMaterial(0, BlackMaterial);
}

// Function called when a chess piece is moved by a player. Takes 1 parameter, its new location
void AChessPiece_Base::ChangeLocation(Atile* newLocation){
	SetActorLocation(FVector(newLocation->GetActorLocation().X, newLocation->GetActorLocation().Y, newLocation->GetActorLocation().Z+10));
	tileOccupied = newLocation;
}

// Left empty for derived classes to redefine
void AChessPiece_Base::DetectSelectableGrids(TArray<Atile*>* SelectableGrids) {
}

// Eliminates piece from the game.
void AChessPiece_Base::Eliminate(){
	this->Destroy();
}

// returns whether the piece is white or not
bool AChessPiece_Base::isWhite() {
	return bIsWhite;
}

// Sets the collision response
void AChessPiece_Base::setOverlap(bool overlap) {
	if (overlap)
		StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	else
		StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
}

void AChessPiece_Base::Discard() {
	this->SetDeselected();
	this->SetActorLocation(FVector(OriginalPosition.X, OriginalPosition.Y, -200));
	this->StaticMesh->SetEnableGravity(false);
	this->StaticMesh->SetVisibility(false, false);
}

void AChessPiece_Base::Reset() {
	this->SetActorLocation(OriginalPosition, false, nullptr, ETeleportType::ResetPhysics);
	this->StaticMesh->SetEnableGravity(true);
	this->StaticMesh->SetVisibility(true, true);
}

void AChessPiece_Base::ResetTiling() {
	OriginalTile->currentOccupyingPiece = this;
	this->tileOccupied = OriginalTile;
}

void AChessPiece_Base::SwitchMaterial(UMaterial* LightM, UMaterial* DarkM) {
	WhiteMaterial = LightM;
	BlackMaterial = DarkM;
	if (isWhite())
		StaticMesh->SetMaterial(0, LightM);
	else
		StaticMesh->SetMaterial(0, DarkM);
}

void AChessPiece_Base::SwitchMaterial(UMaterialInstance* LightM, UMaterialInstance* DarkM) {
	WhiteMaterial = (UMaterial*)LightM;
	BlackMaterial = (UMaterial*)DarkM;
	if (isWhite())
		StaticMesh->SetMaterial(0, LightM);
	else
		StaticMesh->SetMaterial(0, DarkM);
}

int32 AChessPiece_Base::getPiecePoint(){
	return int32(0);
}
