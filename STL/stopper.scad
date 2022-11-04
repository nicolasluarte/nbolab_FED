dim = 22.62;
tol = 0.1;
difference(){
cube([30, 8.5, 8.5]);
translate([4, 3, 2])
cube([dim - tol, 20, 6.5]);
}