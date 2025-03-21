#!/bin/bash

of2306

# Source tutorial run functions
. $WM_PROJECT_DIR/bin/tools/RunFunctions

# timelist="0.001 0.04 0.08 0.099 0.12 0.15"

start_time=$(date +%s)

runApplication reconstructPar
# rm -rf processor*
# scale the STL files and put to the directory of constant/triSurface
for file in cross_section_data/STL/Section*; do
    if [[ -f "$file" ]]; then
        surfaceTransformPoints $file -write-scale 0.001 constant/triSurface/$(basename "$file") > log.post.surfaceTransformPoints
    fi
done

rm -rf postProcessing

# cross section sample: vtp format, cross sections can be viewed in Paraview
python3 "python_scripts/write_SampleDict.py"
postProcess -func sampleSurfaceDict >log.post.sampleSurfaceDict

# surface average: average the pressure and velocity of the cross sections sampled
pimpleFoam -postProcess -dict system/sectionAverageFuncDict > log.post.sectionAverage

# center line probe: centerline, pressure and velocity along the centerline
python3 "python_scripts/write_ProbeDict.py"
postProcess -func probes> log.post.probes

# plot pressure and velocity along the centerline
python3 "python_scripts/plot_u_p_centerline.py"

postProcess -func vorticity > log.post.vorticity
postProcess -func Q > log.post.Q
pimpleFoam -postProcess > log.post.solver

end_time=$(date +%s)

elapsed_time=$((end_time-start_time))
echo "Total time used: $elapsed_time seconds"



