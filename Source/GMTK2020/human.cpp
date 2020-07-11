// Fill out your copyright notice in the Description page of Project Settings.


#include "human.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
// Sets default values
Ahuman::Ahuman()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(GetRootComponent());
	cameraBoom->bDoCollisionTest = true;
	cameraBoom->TargetArmLength = 800;
	cameraBoom->SetRelativeRotation(FRotator(0, 0, 0));
	//cameraBoom->RelativeRotation = FRotator(0.f, 0.f, 0.f);
	cameraBoom->bUsePawnControlRotation = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);


}

// Called when the game starts or when spawned
void Ahuman::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Ahuman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Ahuman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("xAxis", this, &Ahuman::CameraYaw_z);
	PlayerInputComponent->BindAxis("yAxis", this, &Ahuman::CameraPitch_y);


	PlayerInputComponent->BindAxis("forward", this, &Ahuman::moveForward);

}

void Ahuman::CameraYaw_z(float val) {
	FRotator newR = FRotator(0, 0, 0);
	newR.Yaw += val;
	cameraBoom->AddRelativeRotation(newR);

}

void Ahuman::CameraPitch_y(float val) {
	FRotator newR = cameraBoom->GetRelativeRotation();
	newR.Pitch = FMath::Clamp(newR.Pitch + val, -80.0f, 20.0f);

	cameraBoom->SetRelativeRotation(newR);
}

void Ahuman::moveForward(float val) {
	if (Controller != nullptr) {

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, val);
	}
}
