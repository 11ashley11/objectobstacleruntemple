// Fill out your copyright notice in the Description page of Project Settings.


#include "runningobstacle.h"

// Sets default values
Arunningobstacle::Arunningobstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Arunningobstacle::BeginPlay()
{
    
    StartLocation =GetActorLocation();
    FString Name = GetName();
    UE_LOG(LogTemp, Display, TEXT("Beginplay: %s"), *Name);
}

// Called every frame
void Arunningobstacle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    MovePlatform(DeltaTime);
    
    RotatePlatform(DeltaTime);
}
void  Arunningobstacle:: MovePlatform(float DeltaTime)

{
       
 if ( ShouldPlatformReturn())
        {
            FVector MoveDirection = PlatformVelocity.GetSafeNormal();
            StartLocation = StartLocation + MoveDirection*MoveDistance;
            SetActorLocation(StartLocation);
            PlatformVelocity =-PlatformVelocity;
        }
 else
        {
            FVector CurrentLocation = GetActorLocation();
            CurrentLocation = CurrentLocation +  (PlatformVelocity * DeltaTime);
            SetActorLocation(CurrentLocation);
        }
}

void  Arunningobstacle::RotatePlatform(float DeltaTime)
{
    AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool Arunningobstacle::ShouldPlatformReturn() const
{
     return GetDistanceMoved() > MoveDistance;
}

float Arunningobstacle::GetDistanceMoved() const
{
     return FVector::Dist(StartLocation , GetActorLocation());
}

