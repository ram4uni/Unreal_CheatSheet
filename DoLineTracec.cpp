
// AWeek_04_LTFCharacter - Should be your character name

void AWeek_04_LTFCharacter::DoLineTrace()
{

	// =====================================
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	if (!CapsuleComp)
	{
		return;
	}

	// =====================================

	const FVector Start = CapsuleComp->GetComponentLocation();

	const FVector ForwardDir = GetActorForwardVector();

	const FVector End = Start + (ForwardDir * TraceDistance);


	// =====================================

	FHitResult HitResult;

	ECollisionChannel TraceChannel = ECC_Visibility;


	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	/*QueryParams.bTraceComplex = false;*/

	// =====================================

	const bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,      // OUT: hit data
		Start,          // Start
		End,            // End
		TraceChannel,   // Collision channel
		QueryParams     // Extra params (ignore self etc.)
	);

	// =====================================


	if (bDrawDebugTrace)
	{
		// Color: red if no hit, green if hit
		const FColor LineColor = bHit ? FColor::Green : FColor::Red;

		// Draw the line for a short time (duration 0 means one frame; we are calling every Tick anyway)
		DrawDebugLine(
			GetWorld(),
			Start,
			End,
			LineColor,
			false,   // persistent lines?
			0.0f,    // duration
			0,       // depth priority
			2.0f     // thickness
		);
	}

	// =====================================

	if (GEngine)
	{
		if (bHit && HitResult.GetActor())
		{
			AActor* HitActor = HitResult.GetActor();

			const FString NameToPrint = HitActor->GetActorLabel(); // World Outliner name (PIE/editor)

			GEngine->AddOnScreenDebugMessage(
				1,      // same key updates continuously (no spam)
				0.0f,   // one frame, but called every Tick
				FColor::Cyan,
				FString::Printf(TEXT("LineTrace Hit: %s"), *NameToPrint)
			);
		}
	}

}
