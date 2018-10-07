// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/BaseWeapon.h"
#include "UnrealNetwork.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));

	RootComponent = MeshComp;

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

}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

