#!/bin/bash
#for s in {1..10};
c=1
e=5
m=c49a8c6cff
m=0b031f3119
m=0cf2e9402d/scans
m=0d2ee665be/scans
m=0e75f3c4d9/scans
m=0a7cc12c0e/scans
m=0a76e06478/scans
m=785e7504b9/scans
for s in `seq 0 1 20`;
#for s in `seq 3 4 16`;
#for s in `seq 13 4 25`;
do
    #echo $s
    #break
    #./msh2pts ~/data/scannetpp/$m/mesh_aligned_0.05.ply ~/data/scannetpp/$m/near_surf-40m-exp$e-$s.sdf -v -near_surface -num_points 40000000 -near_surface_bias_exponent $e
    #./msh2pts ~/data/scannetpp/$m/mesh_aligned_0.05.ply ~/data/scannetpp/$m/near_surf-140k-exp$e-$s.sdf -v -near_surface -num_points 140000 -near_surface_bias_exponent $e
    ./msh2pts ~/data/scannetpp/$m/mesh_aligned_0.05.ply ~/data/scannetpp/$m/rand_surf-40m-v9-rgb-$s.ply -v -random_surface_points -num_points 40000000 
    #./msh2pts ~/data/scannetpp/$m/mesh_aligned_0.05.ply ~/data/scannetpp/$m/rand_surf-140k-v9-$s.ply -v -random_surface_points -num_points 140000 
    #./msh2pts ~/data/scannetpp/$m/mesh_aligned_0.05.ply ~/data/scannetpp/$m/rand_surf-140k-v9-rgb2-$s.ply -v -random_surface_points -num_points 140000 

    # depre
    #./msh2pts ~/data/scannetpp/$m/mesh_aligned_0.05.ply ~/data/scannetpp/$m/rand_surf-40m-v9-cur$c-$s.ply -v -random_surface_points -num_points 40000000 -curvature_exponent $c
done
