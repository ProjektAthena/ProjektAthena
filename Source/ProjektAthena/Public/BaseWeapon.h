// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class PROJEKTATHENA_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh;
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName WeaponSocketName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;

	//Stats

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float FireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float SPread;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	int NrOfShots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	bool bIsAutomatic;


	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire();
	
	UFUNCTION()
	void Fire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
