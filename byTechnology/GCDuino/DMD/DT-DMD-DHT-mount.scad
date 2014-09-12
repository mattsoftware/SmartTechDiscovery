/*
DT-DMD-DHT-mount
	A 3D printed mounting, to attach a Seeduino which has a DHT22 digital Humidity and Temperature sensor soldered onto it to a Freetronics Dot Matrix Display.
	DavidTangye@gmail.com - 03 Sep 2014
*/

holeD = 3.7;

dmdX = 23;
dmdHoleInX = 15;		// Back in from right edge (dmdX)
dmdHoleGapY = 80;
dmdY=dmdHoleGapY+holeD+10;

lipX = 5;
lipZ = 5;

cdX = 68;
cdY = 55;
cdUpprHoleX = 15;  // From the left edge
cdUpprHoleY = 52;	 // Up from the lower edge 
cdLwrHoleX = 66;  // From the left edge
cdLwrHoleY = 8;    // Up from the lower edge
dhtUpperHoleY = 15; // up from Seeduino Y centre

dhtHigh = 25;
dhtWide = 15;
dhtGap = 3;
dhtUp = 30;   // Up from lower edge seeduino to DHT

highY = max(dmdY,cdX+dhtHigh+dhtGap); // zz
dhtMountLiftY = highY/2 + 35; // Lift to align the cable.

theZ = 5;


Xx = 0.1;
$fn=12;

module DMDmount() {
	difference() {
		cube([dmdX,dmdY,theZ]);
		translate([dmdX-dmdHoleInX,dmdY/2,-Xx]) {
			translate([0,dmdHoleGapY/2,0])
				cylinder(r=holeD/2,h=2*Xx+theZ);
			translate([0,-dmdHoleGapY/2,0])
				cylinder(r=holeD/2,h=2*Xx+theZ);
		}
	}
}

module SeeduinoMount() {
	difference() {
		cube([cdX+Xx,cdY,theZ]);
		translate([cdLwrHoleX+Xx,cdLwrHoleY,-Xx])
			cylinder(r=holeD/2,h=2*Xx+theZ);
		translate([cdUpprHoleX+Xx,cdUpprHoleY,-Xx])
			cylinder(r=holeD/2,h=2*Xx+theZ);
	}
}

module DHTmount() {
	translate([-Xx,0,0]) // Workaround for bug in openscad
		SeeduinoMount();
	translate([cdX,dhtUp,0])
		difference() {
			cube([dhtHigh+dhtGap,dhtWide,theZ]);
			translate([dhtHigh+dhtGap-3,dhtWide/2,0])
				cylinder(r=holeD/2,h=2*Xx+theZ);
		}
}

	translate([0,-dmdY/2,0])
		DMDmount();
	translate([0,-highY/2,0]) {
		translate([dmdX,0,0])
			cube([lipX,highY,theZ+lipZ]);
		translate([dmdX+lipX,dhtMountLiftY,0])
			rotate([0,0,-90])
			DHTmount();
	}
