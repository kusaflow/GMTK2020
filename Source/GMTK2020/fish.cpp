// Fill out your copyright notice in the Description page of Project Settings.


#include "fish.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/Object.h"
#include "GameFramework/Controller.h"
// Sets default values
Afish::Afish()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(GetRootComponent());
	cameraBoom->bDoCollisionTest = true;
	cameraBoom->TargetArmLength = 800;
	cameraBoom->SetRelativeRotation(FRotator(340, 0, 0));
	//cameraBoom->RelativeRotation = FRotator(0.f, 0.f, 0.f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void Afish::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Afish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetCharacterMovement()->AddImpulse(FVector(cameraBoom->GetForwardVector().X * 5000000 * DeltaTime, cameraBoom->GetForwardVector().Y * 5000000 * DeltaTime, 0));

}

// Called to bind functionality to input
void Afish::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	PlayerInputComponent->BindAxis("xAxis", this, &Afish::CameraYaw_z);
	PlayerInputComponent->BindAxis("yAxis", this, &Afish::CameraPitch_y);


	//PlayerInputComponent->BindAxis("forward", this, &Afish::moveForward);

	PlayerInputComponent->BindAction("jump", IE_Pressed, this, &Afish::myJump);

	
}

void Afish::CameraYaw_z(float val) {
	FRotator newR = FRotator(0, 0, 0);
	newR.Yaw += val;
	cameraBoom->AddRelativeRotation(newR);

	//RootComponent->GetChildComponent(1)->AddRelativeRotation(newR);

}

void Afish::CameraPitch_y(float val) {
	FRotator newR = cameraBoom->GetRelativeRotation();
	newR.Pitch = FMath::Clamp(newR.Pitch + val, -80.0f, 20.0f);

	cameraBoom->SetRelativeRotation(newR);


}

void Afish::moveForward(float val) {
	if (Controller != nullptr) {

		const FRotator Rotation = cameraBoom->GetComponentRotation();//Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, val);
	}
}

void Afish::myJump() {
	GetCharacterMovement()->Velocity = cameraBoom->GetForwardVector() * 50;
	
	Jump();

	GetCharacterMovement()->Velocity = FVector(0);
}