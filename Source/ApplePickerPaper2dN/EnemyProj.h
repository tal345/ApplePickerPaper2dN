// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "EnemyProj.generated.h"

UCLASS()
class APPLEPICKERPAPER2DN_API AEnemyProj : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyProj();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UPaperFlipbookComponent* FBProjectile;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AEnemyProj, Meta = (ExposeOnSpawn = "true"))
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AEnemyProj)
		float LinearDamping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AEnemyProj)
		UPaperFlipbook* EndAnimation;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnProjHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnAnimEnd();

	UFUNCTION(BlueprintImplementableEvent)
		void ProjMissed();
	
	UFUNCTION(BlueprintImplementableEvent)
		void ProjDest();

	UFUNCTION(BlueprintCallable, Category = ABulletManagerPFCC)
		void DestroyProj();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	
};
