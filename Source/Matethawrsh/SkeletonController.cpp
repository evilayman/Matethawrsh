// Fill out your copyright notice in the Description page of Project Settings.

#include "SkeletonController.h"

// Sets default values for this component's properties
USkeletonController::USkeletonController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
}


// Called when the game starts
void USkeletonController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SkeletalMesh = this->GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	PoseableMesh = this->GetOwner()->FindComponentByClass<UPoseableMeshComponent>();

	SkeletalMesh->bEnableUpdateRateOptimizations = true;
	//SkeletalMesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPoseAndRefreshBones;
	SkeletalMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	SkeletonBoneNames = SkeletalMesh->GetAllSocketNames();

	BoneNumber = SkeletalMesh->GetNumBones();	
}


// Called every frame
void USkeletonController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (!RewindStarted)
	{
		for (size_t i = 0; i < BoneNumber; i++)
		{
			auto trans = SkeletalMesh->GetSocketTransform(SkeletonBoneNames[i], RTS_World);

			PoseableMesh->SetBoneTransformByName(SkeletonBoneNames[i], trans, EBoneSpaces::WorldSpace);
		}
	}
	else
	{
		SetCurrentBones(BoneTransforms);
	}
}

void USkeletonController::SetCurrentBones(TArray<FTransform> &boneTransforms)
{
	for (size_t i = 0; i < boneTransforms.Num(); i++)
	{
		auto trans = boneTransforms[i];

		PoseableMesh->SetBoneTransformByName(SkeletonBoneNames[i], trans, EBoneSpaces::WorldSpace);
	}

	BoneTransforms.Empty();
}
