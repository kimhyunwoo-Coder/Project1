

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DownSPawnActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class SPARTAPROJECT_API ADownSPawnActor : public AActor
{
    GENERATED_BODY()

public:
    
    ADownSPawnActor();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Components")
    USceneComponent* SceneRoot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
    UStaticMeshComponent* StaticMeshComp;
    
    virtual void BeginPlay() override;

public:
    
    virtual void Tick(float DeltaTime) override;

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
    float RotationSpeed;

   
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
    float MoveSpeed;

 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
    FVector MoveRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
    FVector MoveDirection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
    FVector DestroyObstaclen;

    
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* BoxComponent;

   
    FTimerHandle TimerHandle;

    
    FTimerHandle DestroyTimerHandle;

  
    void InitializeObstacle();

  
    void ChangeMoveDirection();

   
    UFUNCTION()
    void OnPlayerHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    
    void DestroyObstacle();
};