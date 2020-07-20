Library IEEE;
use IEEE.STD_LOGIC_1164.all;

ENTITY xor2 IS
	GENERIC(t_xor : time := 4 ns);
	PORT( x, y: IN STD_LOGIC;
		    z: OUT STD_LOGIC);
END xor2;

ARCHITECTURE dataflow OF xor2 IS

BEGIN

	z <= x XOR y AFTER t_xor;

END dataflow;
