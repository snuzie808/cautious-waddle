// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"
#include "Ball.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PaddlePawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APaddle::APaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set this pawn to be controlled by the lowest number player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("PaddleCollisionComponent"));
	VisualComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleVisualComponent"));

	RootComponent = CollisionComponent;

	// Set up CollisionComponent as parent of VisualComponent
	VisualComponent->SetupAttachment(CollisionComponent);

	VisualComponent->BodyInstance.SetCollisionProfileName("NoCollision");

	CollisionComponent->BodyInstance.SetCollisionProfileName("Pawn");

	CollisionComponent->OnComponentHit.AddDynamic(this, &APaddle::OnHit);

}


void APaddle::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Paddle has been hit by: %s"), *OtherActor->GetName()));

		//Get Ball
	}
}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis(TEXT("MovePaddle"), this, &APaddle::Move_ZAxis);

}

float APaddle::GetZVelocity() const
{
	return ZVelocity;
}

