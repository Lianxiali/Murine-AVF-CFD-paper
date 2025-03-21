
    // 1. mag(wallShearStress) file in each time step folder.
    magwallShearStress
    {
        // Mandatory entries (unmodifiable)
        type            mag;
        libs            (fieldFunctionObjects);

        // Mandatory (inherited) entries (runtime modifiable)
        field           wallShearStress;


        // Optional (inherited) entries
        result  mag_tau;  // rename mag(wallShearStress) to mag_tau
        region          region0;
        enabled         true;
        timeStart       0;
        timeEnd         1000;
        executeControl  writeTime;
        executeInterval 1;
        writeControl    writeTime;
        writeInterval   1;
        log             false;
    }

    // 1. wallShearStressMean file in each time step folder
    mean_tau
    {
        type                fieldAverage;
        libs  (fieldFunctionObjects);
        timeStart           0;
        writeControl    writeTime;
        writeInterval   1;
        log     false;
        fields
        (
            wallShearStress
            {
                mean        on;
                prime2Mean  off;
                base        time;  // time average

                window      0.1258;
                windowType  exact;  //(none approximate exact)

                allowRestart no;
            }
            mag_tau // mag(wallShearStress)Mean file in each time step folder
            {
                mean        on;
                prime2Mean  off;
                base        time;  // time average
                windowType  exact;  //(none approximate exact)
                window      0.1258;
                allowRestart no;
            }
        );
    }




    // TAWSS1
    // {
    //     type exprField;
    //     libs (fieldFunctionObjects);

    //     writeControl    timeStep;
    //     writeInterval   1;

    //     action new; // no, new(default), modify
    //     field TAWSS;
    //     //readFields (wallShearStress mag_tauMean);

    //     autowrite true; //default: false
    //     store     true; //default: true  store on the object-registry
    //     dimensions [0 2 -2 0 0 0 0];
    //     //fieldMask "(mag(pos()) < 0 && mag(pos.y()) > 0)";
    //     expression "mag_tauMean*1000";

    //     // dimension [Pa];
    // }



    TAWSS_OSI
    {
        libs (utilityFunctionObjects);
        type coded;
        name tawss_osi_code; // Name of on-the-fly generated functionObject
        writeControl    runTime;
        timeStart       0.1258;
        writeInterval   0.1258;

        codeOptions
        #{
            -I$(LIB_SRC)/meshTools/lnInclude
        #};
        codeWrite
        #{
            const volScalarField& magtau_mean = (mesh().lookupObject<volScalarField>("mag_tauMean"));
            const volVectorField& tau_mean = (mesh().lookupObject<volVectorField>("wallShearStressMean"));
            const dimensionedScalar epstau = dimensionedScalar("epstau", magtau_mean.dimensions(), SMALL);
            // Info << magtau_mean.dimensions()<<"2" << nl;
            volScalarField osi
            (
                IOobject
                (
                    "OSI",
                    mesh().time().timeName(),
                    mesh(),
                    IOobject::NO_READ,
                    IOobject::AUTO_WRITE
                ),
                0.5*(1 - (mag(tau_mean) + epstau) / (magtau_mean + epstau))
            );
            // osi.ref() = dimensionedScalar("OSI", osi.dimensions(), 0);

            const dimensionedScalar rho = dimensionedScalar("epstau", dimDensity, 1000);
            volScalarField tawss
            (
                IOobject
                (
                    "TAWSS",
                    mesh().time().timeName(),
                    mesh(),
                    IOobject::NO_READ,
                    IOobject::AUTO_WRITE
                ),
                magtau_mean*rho
            );

            osi.write();
            tawss.write();
        #};
    }

