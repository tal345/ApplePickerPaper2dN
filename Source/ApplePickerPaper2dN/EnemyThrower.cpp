// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyThrower.h"

// Sets default values
AEnemyThrower::AEnemyThrower()
	:FBEnemy(nullptr)
	,DeltaLoc(1.0f,0.0f,0.0f)
	

{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ShootTimer.Invalidate();
	FBEnemy = CreateDefaultSubobject<UPaperFlipbookComponent>("FBProjectile");
	RootComponent = FBEnemy;
	Tags.Add("FBEnemy");
	FBEnemy->ComponentTags.Add("FBEnemy");	
}

// Called when the game starts or when spawned
void AEnemyThrower::BeginPlay()
{
	Super::BeginPlay();

	FTimerDelegate TimerSpawnDel;
	auto TimerSpawnLambda = [this]()
	{
		GetWorld()->SpawnActor(ProjClass.Get(), &GetActorTransform());
	};

	if (!TimerSpawnDel.IsBound())
	{
		TimerSpawnDel.BindLambda(TimerSpawnLambda);
		GetWorld()->GetTimerManager().SetTimer(ShootTimer, TimerSpawnDel, 1.0f, true);
	}
	
	

	FTimerDelegate TimerChDirDel;
	auto TimerChDirLambda = [this]()
	{
		if (FMath::RandRange(0.0f, 1.0f) < 0.02f)
		{
			DeltaLoc.X *= -1.0f;
		}
	};

	if (!TimerChDirDel.IsBound())
	{
		TimerChDirDel.BindLambda(TimerChDirLambda);
		GetWorld()->GetTimerManager().SetTimer(RanDirTimer, TimerChDirDel, 0.02f, true);
	}
	
	FBEnemy->SetNotifyRigidBodyCollision(true);
	FScriptDelegate HitDel;
	HitDel.BindUFunction(this, "OnEnemyHit");
	FBEnemy->OnComponentHit.Add(HitDel);
	
}



// Called every frame
void AEnemyThrower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(DeltaLoc, true);
}

void AEnemyThrower::OnEnemyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DeltaLoc.X *= -1.0f;
}

void AEnemyThrower::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(ShootTimer);
	GetWorld()->GetTimerManager().ClearTimer(RanDirTimer);
	FBEnemy->SetNotifyRigidBodyCollision(false);
	FBEnemy->OnComponentHit.Clear();
}

void AEnemyThrower::PauseEnemy()
{
	SetActorTickEnabled(false);
	GetWorld()->GetTimerManager().PauseTimer(ShootTimer);
	GetWorld()->GetTimerManager().PauseTimer(RanDirTimer);
	
}
