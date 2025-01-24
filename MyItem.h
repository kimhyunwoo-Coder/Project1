#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyItem.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SPARTAPROJECT_API AMyItem : public AActor
{
	GENERATED_BODY()

public:
	
	AMyItem();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float MaxRange;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Properties")
	bool bMovingForward;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Properties")
	bool bMovingUpward;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Properties")
	bool bMoveOnXAxis;

	FVector StartLocation;

	
	virtual void BeginPlay() override;

	
	virtual void Tick(float DeltaTime) override;

	
	UFUNCTION(BlueprintCallable, Category = "Item|Action")
	void ResetActorPosition();

	
	UFUNCTION(BlueprintCallable, Category = "Item|Action")
	void SetMovementAxis(bool bMoveOnX);
};