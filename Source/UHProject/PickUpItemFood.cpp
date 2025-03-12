#include "PickUpItemFood.h"

void APickUpItemFood::SetUdon()
{
    ItemMesh->SetMaterial(0, MaterialArray[0]);
}

void APickUpItemFood::SetRamen()
{
    ItemMesh->SetMaterial(0, MaterialArray[1]);
}
