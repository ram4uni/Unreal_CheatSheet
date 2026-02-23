

void AMovingBox::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->AddMappingContext(MappingContext, 0);
			}
		}
	
		if (UEnhancedInputComponent* EIC =
			Cast<UEnhancedInputComponent>(PC->InputComponent)) {

			if (PrintAction)
			{
				EIC->BindAction(
					PrintAction,
					ETriggerEvent::Started,
					this,
					&AMovingBox::PrintMessage
				);
			}


			if (JumpAction)
			{
				EIC->BindAction(
					JumpAction,
					ETriggerEvent::Started,
					this,
					&AMovingBox::Jump
				);
			}
			
			if (MoveAction)
			{
				EIC->BindAction(
					MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AMovingBox::Move
				);
			}
		}

	}	
}



void AMovingBox::PrintMessage()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,                 // New message every time
			2.0f,               // Duration (seconds)
			FColor::Green,      // Text colour
			TEXT("Hello from the Cube!")
		);
	}

}



void AMovingBox::Jump() {
	if (!BoxMesh) return;

	// Prevent jumping in mid-air (simple ground check)
	if (BoxMesh->GetPhysicsLinearVelocity().Z == 0.f)
	{
		BoxMesh->AddImpulse(
			FVector(0.f, 0.f, JumpImpulse),
			NAME_None,
			true
		);
	}
}

void AMovingBox::Move(const FInputActionValue& Value)
{
	const FVector2D Input = Value.Get<FVector2D>();

	FVector DeltaMove = FVector(
		Input.Y,   // Forward / Back
		Input.X,   // Right / Left
		0.f
	) * MoveSpeed * GetWorld()->GetDeltaSeconds();

	AddActorWorldOffset(DeltaMove, true);

}