Library IEEE;
use IEEE.STD_LOGIC_1164.all;

ENTITY or2 IS
	GENERIC(t_or : time := 4 ns);
	PORT( x, y: IN STD_LOGIC;
		    z: OUT STD_LOGIC);
END or2;

ARCHITECTURE dataflow OF or2 IS

BEGIN
	z <= x OR y AFTER t_or;
END dataflow;
