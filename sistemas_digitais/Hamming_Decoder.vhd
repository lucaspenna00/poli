-- Polytechnic School of the University of Sao Paulo
-- Digital System and Computer Engineering Department
-- Digital Laboratory A - Experience 5
-- Hamming Decoder H(7,4)
-- Authors: Lucas Penna Saraiva and Stefan R. Raposo

entity decHamming is
	port (
		hamming: in bit_vector(6 downto 0);
		binary: out bit_vector(3 downto 0);
		error: out bit
		);
end entity;

architecture Behaviour of decHamming is

	-- signal
	
	signal erro1 : bit;  
	signal erro2 : bit;
	signal erro3 : bit;
	
	-- hamming decoding
	
	begin
	
		-- error detection
	
		erro1 <= hamming(0) xor hamming(2) xor hamming(4) xor hamming(6);
		erro2 <= hamming(0) xor hamming(1) xor hamming(4) xor hamming(5);
		erro3 <= hamming(0) xor hamming(1) xor hamming(2) xor hamming(3);
		
		error <= erro1 or erro2 or erro3;
		
		
		-- final decoding and error correction
		
		binary(0) <= hamming(0) xor (erro1 and erro2 and erro3);
		binary(1) <= hamming(1) xor (not erro1 and erro2 and erro3);
		binary(2) <= hamming(2) xor (erro1 and not erro2 and erro3);
		binary(3) <= hamming(4) xor (erro1 and erro2 and not erro3);
		
end Behaviour;
