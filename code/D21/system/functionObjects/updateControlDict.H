    updateControlDict
    {
        type timeActivatedFileUpdate;
        libs (utilityFunctionObjects);
        writeControl timeStep;
        writeInterval 1;
        fileToUpdate "<system>/controlDict";
        timeVsFile
        (
            (-1 "<system>/controlDict")
            (0.08 "<system>/controlDict.1")
            (0.15 "<system>/controlDict.2")
        );
    }
