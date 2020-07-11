// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Spider.generated.h"

UCLASS()
class GMTK2020_API ASpider : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpider();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* cameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "myVar")
	TSubclassOf<class Ahuman> char1;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "myVar")
		TSubclassOf<class Afish> char2;

	UPROPERTY(BlueprintReadWrite, category = "myVar")
	bool isPoss = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void CameraYaw_z(float val);

	UFUNCTION()
	void CameraPitch_y(float val);

	UFUNCTION()
	void moveForward(float val);

};
