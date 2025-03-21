    pu_ave_proximal_artery
    {
        // Mandatory entries (unmodifiable)
        type            surfaceFieldValue;
        libs            (fieldFunctionObjects);

        // Mandatory entries (runtime modifiable)
        fields          (U p);
        operation       areaAverage;
        regionType      patch;
        name            proximal_artery;

        // Optional entries (runtime modifiable)
        postOperation   none;
        scaleFactor     1.0;
        writeArea       true;
        surfaceFormat   none;

        // Optional (inherited) entries
        writeFields     false;
        scalingFactor   1.0;
        writePrecision  8;
        writeToFile     true;
        useUserTime     true;
        region          region0;
        enabled         true;
        log             true;
        timeStart       0;
        timeEnd         1000;
        executeControl  timeStep;
        executeInterval 1;
        writeControl    timeStep;
        writeInterval   1;
    }

    surfaceFieldValue_vein
    {
        pu_ave_proximal_artery
        name            vein;
    }

    pu_ave_distal_artery
    {
        pu_ave_proximal_artery
        name            distal_artery;

    }
