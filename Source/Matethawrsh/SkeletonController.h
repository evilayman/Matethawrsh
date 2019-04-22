// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Array.h"
#include "SkeletonController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MATETHAWRSH_API USkeletonController : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkeletonController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetCurrentBones(TArray<FTransform> &boneTransforms);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	bool RewindStarted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	TArray<FTransform> BoneTransforms;

private:
	UPoseableMeshComponent *PoseableMesh;
	USkeletalMeshComponent *SkeletalMesh;
	TArray<FName> SkeletonBoneNames;
	int32 BoneNumber;
};
