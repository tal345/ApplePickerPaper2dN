// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyThrower.generated.h"

UCLASS()
class APPLEPICKERPAPER2DN_API AEnemyThrower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyThrower();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UPaperFlipbookComponent* FBEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AEnemyThrower)
		TSubclassOf<AActor> ProjClass;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
		void OnEnemyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
	FVector DeltaLoc;


	FTimerHandle ShootTimer;
	FTimerHandle RanDirTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = AEnemyThrower)
		void PauseEnemy();

};
