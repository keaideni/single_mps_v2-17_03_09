#!/bin/sh

mkdir Corr
mkdir data
mkdir result
mkdir data/SiteWave
mkdir data/SubLattice

cat > data/QNosave <<EOF
LatticeSize= 10
ParticleNo= 10
SiteNo= 1
DeltaQL= 1
DeltaQR= 2
D= 10
SweepNo= 2
EdgeCondition= 1
Energy= 0
u= 1
t= 1
epsilon= 0
EOF
