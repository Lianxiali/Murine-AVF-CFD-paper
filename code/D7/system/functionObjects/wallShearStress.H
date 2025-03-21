    // This will produce two files:
    // 1. postProcessing/tau/wallShearStress.dat: including the min, max wall shear stress of the patch at each time step.
    // 2. wallShearStress field in each time step folder.
	tau
	{
		// Mandatory entries (unmodifiable)
		type            wallShearStress;
		libs            (fieldFunctionObjects);

		// Optional entries (runtime modifiable)
		patches         (wall); // (wall1 "(wall2|wall3)");
		writeControl        writeTime;
	}
