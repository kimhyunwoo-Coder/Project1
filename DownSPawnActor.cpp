#include "DownSPawnActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"



ADownSPawnActor::ADownSPawnActor()
{
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);


    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComp->SetupAttachment(SceneRoot);

    
    PrimaryActorTick.bCanEverTick = true;


   
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    BoxComponent->SetupAttachment(RootComponent);

   
    RotationSpeed = 10.0f;
    MoveSpeed = 100.0f;
    MoveRange = FVector(500.0f, 500.0f, 0.0f); 
    MoveDirection = FVector(1.0f, 0.0f, 0.0f); 

   
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADownSPawnActor::OnPlayerHit);
}


void ADownSPawnActor::BeginPlay()
{
    Super::BeginPlay();

    
    InitializeObstacle();


    GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ADownSPawnActor::DestroyObstacle, 20.0f, false);  
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADownSPawnActor::ChangeMoveDirection, 2.0f, true);
}


void ADownSPawnActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

   
    FRotator NewRotation = GetActorRotation() + FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f);
    SetActorRotation(NewRotation);

    
    FVector NewLocation = GetActorLocation() + MoveDirection * MoveSpeed * DeltaTime;

    
    FVector ClampedLocation = FVector(
        FMath::Clamp(NewLocation.X, -MoveRange.X, MoveRange.X),
        FMath::Clamp(NewLocation.Y, -MoveRange.Y, MoveRange.Y),
        NewLocation.Z 
    );

    SetActorLocation(ClampedLocation);
}


void ADownSPawnActor::InitializeObstacle()
{
    
    RotationSpeed = FMath::RandRange(10.0f, 50.0f);
    MoveSpeed = FMath::RandRange(50.0f, 150.0f);
}



void ADownSPawnActor::ChangeMoveDirection()
{
   
    if (FMath::RandBool())
    {
        MoveDirection = FVector(FMath::RandRange(-1.0f, 1.0f), 0.0f, 0.0f);
    }
    else
    {
        MoveDirection = FVector(0.0f, FMath::RandRange(-1.0f, 1.0f), 0.0f); 
    }
}


void ADownSPawnActor::OnPlayerHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        
        UE_LOG(LogTemp, Warning, TEXT("Player Hit the Obstacle!"));
    }
}
void ADownSPawnActor::DestroyObstacle()
{
  
    Destroy();
    UE_LOG(LogTemp, Warning, TEXT("Obstacle has been destroyed after 10 seconds!"));
}
