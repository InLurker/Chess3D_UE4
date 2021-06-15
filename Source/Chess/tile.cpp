#include "tile.h"
#include "ChessPiece_Base.h"

// Sets default values
Atile::Atile() {
	PrimaryActorTick.bCanEverTick = true;
	//Create static mesh of component "cube"
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));

	//Load cube mesh
	UStaticMesh* cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
 	
	//Set component's mesh
	StaticMesh->SetStaticMesh(cubeMesh);

	//Set as root component
	RootComponent = StaticMesh;

	//Resize the object
	StaticMesh->SetWorldScale3D(FVector(2, 2, 0.2));

	//Sets the material of tiles
	LightMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Materials/BnW(Default)/tile_W.tile_W'")).Object;
	DarkMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Materials/BnW(Default)/tile_B.tile_B'")).Object;
	HighlightMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Materials/Highlights/Select_Highlight.Select_Highlight'")).Object;
}

// Called when the game starts or when spawned
void Atile::BeginPlay() {
	Super::BeginPlay();
	
}
// Called every frame
void Atile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Atile::switchMaterial(UMaterial* LightM, UMaterial* DarkM) {
	//assigns the new material
	LightMaterial = LightM;
	DarkMaterial = DarkM;

	//applies the material
	if (isBlack)
		StaticMesh->SetMaterial(0, DarkMaterial);
	else
		StaticMesh->SetMaterial(0, LightMaterial);
}

void Atile::switchMaterial(UMaterialInstance* LightM, UMaterialInstance* DarkM) {
	//assigns the new material
	LightMaterial = (UMaterial*)LightM;
	DarkMaterial = (UMaterial*)DarkM;

	//applies the material
	if (isBlack)
		StaticMesh->SetMaterial(0, DarkMaterial);
	else
		StaticMesh->SetMaterial(0, LightMaterial);
}

void Atile::occupy(AChessPiece_Base* newPiece) {
	//Assigns the new piece to this object
	if (isOccupied()) {
		currentOccupyingPiece->Discard();
	}
	newPiece->ChangeLocation(this);
	currentOccupyingPiece = newPiece;
	unhighlight();
}

void Atile::unoccupy() {
	//unassign the current occupying piece
	currentOccupyingPiece = nullptr;
	unhighlight();
}

void Atile::highlight() {
	//highlights this object
	StaticMesh->SetMaterial(0, HighlightMaterial);
	if (isOccupied())
		currentOccupyingPiece->SetEliminateMaterial();
}

void Atile::unhighlight() {
	//restore the object to its inital state
	if (isBlack)
		StaticMesh->SetMaterial(0, DarkMaterial);
	else
		StaticMesh->SetMaterial(0, LightMaterial);

	if (isOccupied())
		currentOccupyingPiece->SetDeselected();
}

bool Atile::isOccupied() {
	//returns false if current occupying piece is null
	return (currentOccupyingPiece != nullptr);
};