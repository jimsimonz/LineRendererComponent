// Copyright Peter Leontev

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "LineMeshComponent.generated.h"


class FPrimitiveSceneProxy;
class FLineMeshSceneProxy;
struct FLineMeshSection;


UCLASS(hidecategories = (Object, LOD), meta = (BlueprintSpawnableComponent))
class LINERENDERER_API ULineMeshComponent : public UMeshComponent
{
	GENERATED_BODY()

public:
	ULineMeshComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Components|LineRenderer")
	void CreateLine2Points(int32 SectionIndex, const FVector& StartPoint, const FVector& EndPoint, const FColor& Color, float Thickness);

	UFUNCTION(BlueprintCallable, Category = "Components|LineRenderer")
	void CreateLine(int32 SectionIndex, const TArray<FVector>& Vertices, const FColor& Color, float Thickness);

	UFUNCTION(BlueprintCallable, Category = "Components|LineRenderer")
	void UpdateLine(int32 SectionIndex, const TArray<FVector>& InVertices, const FLinearColor& Color);

	UFUNCTION(BlueprintCallable, Category = "Components|LineRenderer")
	void RemoveLine(int32 SectionIndex);

	UFUNCTION(BlueprintCallable, Category = "Components|LineRenderer")
	void RemoveAllLines();

	UFUNCTION(BlueprintCallable, Category = "Components|LineRenderer")
	void SetLineVisible(int32 SectionIndex, bool bNewVisibility);

	UFUNCTION(BlueprintCallable, Category = "Components|LineRenderer")
	bool IsLineVisible(int32 SectionIndex) const;

	/** Returns number of sections currently created for this component */
	UFUNCTION(BlueprintCallable, Category = "Components|LineRenderer")
	int32 GetNumLines() const;

	//~ Begin UPrimitiveComponent Interface.
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	//~ End UPrimitiveComponent Interface.

public:
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// UMaterialInterface* Material;

private: 
	FLinearColor CreateOrUpdateSectionColor(int32 SectionIndex, const FLinearColor& Color);

	//~ Begin USceneComponent Interface.
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
	//~ Begin USceneComponent Interface.

	/** Update LocalBounds member from the local box of each section */
	void UpdateLocalBounds();

private:
    UPROPERTY()
    TMap<int32, FLinearColor> SectionColors;

    friend class FLineMeshSceneProxy;
};


