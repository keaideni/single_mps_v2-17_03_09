#!/bin/sh

mkdir Corr
mkdir data
mkdir result
mkdir data/SiteWave

cat > data/QNosave <<EOF
LatticeSize= 20
ParticleNo= 10
SiteNo= 1
DeltaQL= 1
DeltaQR= 2
D= 200
SweepNo= 3
EdgeCondition= 1
Energy= 0
u= 1
t= 0.12
EOF
