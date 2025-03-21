foamCleanTutorials
touch 0925C2D7.foam
# blockMesh | tee log.blockMesh
# surfaceFeatureExtract | tee  log.surfaceFeatureExtract
# snappyHexMesh | tee log.snappyHexMesh


cd constant/triSurface
cat proximal_artery.stl distal_artery.stl vein.stl wall.stl > AVF.stl
surfaceFeatureEdges AVF.stl AVF.fms
cd ../../

# using cfMesh
# cartesianMesh
tetMesh
#pMesh

transformPoints -scale 0.001
checkMesh
