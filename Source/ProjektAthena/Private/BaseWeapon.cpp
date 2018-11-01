// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/BaseWeapon.h"
#include "UnrealNetwork.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h" 
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));

	RootComponent = MeshComp;

	NrOfShots = 1;

	bIsAutomatic = false;

	WeaponSocketName = "WeaponSocket";

	SetReplicates(true);

}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseWeapon::ServerFire_Implementation()
{
	Fire();
}

bool ABaseWeapon::ServerFire_Validate()
{
	return true;
}

void ABaseWeapon::Fire()
{
	if (Role < ROLE_Authority)
	{
		ServerFire();
	}
	AActor* MyOwner = GetOwner();

	PlayFireEffects();

	for (int i = 1; i <= NrOfShots; i++)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);


		FVector ShotDirection = EyeRotation.Vector();

		float HalfRad = FMath::DegreesToRadians(Spread);
		ShotDirection = FMath::VRandCone(ShotDirection, HalfRad, HalfRad);

		FVector TraceEnd = EyeLocation + (ShotDirection * 10000);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;
		QueryParams.bReturnPhysicalMaterial = true;

		FVector TraceEndPoint = TraceEnd;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Cyan, false, 1.0f, 0, 1.0f);
		}
	}

}

void ABaseWeapon::PlayFireEffects()
{

}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

