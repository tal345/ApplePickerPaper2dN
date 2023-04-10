// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProj.h"

// Sets default values
AEnemyProj::AEnemyProj()
	:FBProjectile(nullptr)
	,LinearDamping(0.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FBProjectile = CreateDefaultSubobject<UPaperFlipbookComponent>("FBProjectile");
	RootComponent = FBProjectile;
	Tags.Add("FBProjectile");
	FBProjectile->ComponentTags.Add("FBProjectile");

}

// Called when the game starts or when spawned
void AEnemyProj::BeginPlay()
{
	Super::BeginPlay();
	FBProjectile->SetLooping(true);

	FBProjectile->SetLinearDamping(LinearDamping);	
	FBProjectile->SetEnableGravity(true);
	FBProjectile->SetSimulatePhysics(true);

	FBProjectile->SetNotifyRigidBodyCollision(true);
	FScriptDelegate HitDel;
	HitDel.BindUFunction(this, "OnProjHit");
	FBProjectile->OnComponentHit.Add(HitDel);

	FScriptDelegate FPlayDel;
	FPlayDel.BindUFunction(this, "OnAnimEnd");
	FBProjectile->OnFinishedPlaying.Add(FPlayDel);
}

// Called every frame
void AEnemyProj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyProj::OnProjHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->ComponentHasTag("Floor"))
	{
		ProjMissed();
		//GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::White, FString::Printf(TEXT("AEnemyProj::OnProjHit: Floor")));
	}
	else
	{
		ProjDest();
	}
	DestroyProj();
}

void AEnemyProj::OnAnimEnd()
{
	FBProjectile->OnFinishedPlaying.Clear();
	Destroy();
}

void AEnemyProj::DestroyProj()
{
	FBProjectile->SetNotifyRigidBodyCollision(false);
	FBProjectile->OnComponentHit.Clear();
	FBProjectile->SetLooping(false);
	FBProjectile->SetEnableGravity(false);
	FBProjectile->SetSimulatePhysics(false);
	FBProjectile->SetFlipbook(EndAnimation);
}

void AEnemyProj::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DestroyProj();
}

