module base(){
import("/home/nicoluarte/nbolab_FED/STL/base.stl");
}
module uplift(){
translate([-95, -32.5, -8])
rotate([90, 0, 90])
    difference(){
cube([60.30, 9.65, 9.65]);
translate([00,0,0])
rotate([45,0,0])
cube([60.30, 20, 9.65]);
}
}

module stop(){
translate([-78, -38, 51.7])
rotate([0, 0, 90])
color("blue")
import("/home/nicoluarte/3dprints/wedge.stl");
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
uplift();
stop();
 
color("blue")
translate([-42, -52.471, 32])   
cube([12, 1.4, 11]);