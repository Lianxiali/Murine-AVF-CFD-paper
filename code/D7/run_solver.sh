#!/bin/sh
cd ${0%/*} || exit 1    # run from this directory


# Source tutorial run functions
. $WM_PROJECT_DIR/bin/tools/RunFunctions

#foamListTimes -rm
#foamListTimes -rm -processor
rm -r 0
cp -r 0.orig 0
rm -rf log.*
rm -rf postProcessing
#./makemesh.sh
renumberMesh -overwrite
runApplication decomposePar -force
runParallel pimpleFoam
