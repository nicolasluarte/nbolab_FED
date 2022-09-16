module base(){
import("/home/nicoluarte/repos/nbolab_FED/STL/base.stl");
}

module stop(){
translate([-78, -38, 51.7])
rotate([0, 0, 90])
color("blue")
import("/home/nicoluarte/repos/3dprints/wedge.stl");
}

module opening(){
translate([-87, -2.5, 50])
color("red")
cylinder(10, 3.5, 3.5, center = true);
}

difference(){
    base();
    opening();
    }
stop();
 
color("blue")
translate([-42, -52.471, 32])   
cube([12, 1.4, 11]);