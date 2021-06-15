#include "ChessBoard.h"
#include "Kismet/GameplayStatics.h"
#include "tile.h"

// Sets default values
AChessBoard::AChessBoard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize all the materials
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Materials/BnW(Default)/tile_W.tile_W'"));
	if (Material.Object != NULL)
		LightMaterial = (UMaterial*)Material.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> Material2(TEXT("Material'/Game/Materials/BnW(Default)/tile_B.tile_B'"));
	if (Material2.Object != NULL)
		DarkMaterial = (UMaterial*)Material2.Object;
}

// Called when the game starts or when spawned
void AChessBoard::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AChessBoard::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}