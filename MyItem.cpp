#include "MyItem.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

AMyItem::AMyItem()
{
    
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComp->SetupAttachment(SceneRoot);

    
    PrimaryActorTick.bCanEverTick = true;
    MoveSpeed = 500.0f;
    MaxRange = 500.0f;
    bMovingForward = true;   
    bMovingUpward = true;   

    StartLocation = FVector::ZeroVector;

    bMoveOnXAxis = true; 
}

void AMyItem::BeginPlay()
{
    Super::BeginPlay();
}

void AMyItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

   
    float DistanceToMove = MoveSpeed * DeltaTime;

    
    if (bMoveOnXAxis)
    {
        if (bMovingForward)
        {
            SetActorLocation(GetActorLocation() + FVector(DistanceToMove, 0.0f, 0.0f));
        }
        else
        {
            SetActorLocation(GetActorLocation() - FVector(DistanceToMove, 0.0f, 0.0f));
        }
    }
    
    else
    {
        if (bMovingUpward)
        {
            SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, DistanceToMove));  
        }
        else
        {
            SetActorLocation(GetActorLocation() - FVector(0.0f, 0.0f, DistanceToMove));  
        }
    }

   
    if (bMoveOnXAxis)
    {
        float DistanceX = FMath::Abs(GetActorLocation().X - StartLocation.X);
        if (DistanceX >= MaxRange)
        {
            bMovingForward = !bMovingForward;  
            StartLocation.X = GetActorLocation().X;  
        }
    }

    
    if (!bMoveOnXAxis)
    {
        
        float DistanceZ = FMath::Abs(GetActorLocation().Z - StartLocation.Z);

        if (DistanceZ >= MaxRange)
        {
            bMovingUpward = !bMovingUpward;  
            StartLocation.Z = GetActorLocation().Z;  
        }
    }
}

void AMyItem::ResetActorPosition()
{
    SetActorLocation(StartLocation);
}


void AMyItem::SetMovementAxis(bool bMoveOnX)
{
    bMoveOnXAxis = bMoveOnX;
    StartLocation = GetActorLocation(); 
}