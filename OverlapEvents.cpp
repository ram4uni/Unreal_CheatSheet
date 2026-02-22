

//Overlap Begin/End Signature

UFUNCTION()
void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                    bool bFromSweep, const FHitResult& SweepResult);

UFUNCTION()
void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
