-- Polytechnic School of the University of Sao Paulo
-- Digital System and Computer Engineering Department
-- Digital Laboratory A - Experience 5
-- Hamming Encoder H(7,4)
-- Authors: Lucas Penna Saraiva and Stefan R. Raposo

entity Hamming_Encoder74 is
	port(
		binary: in bit_vector(3 downto 0);
		hamming: out bit_vector(6 downto 0)
		);
end entity;


architecture Behaviour of Hamming_Encoder74 is

	-- signal
	
	signal parity1 : bit;  
	signal parity2 : bit;
	signal parity3 : bit;
	signal hamming_aux : bit_vector(6 downto 0);
	
	-- hamming encoding
	
	begin
	
	hamming_aux(0) <= binary(0);
	hamming_aux(1) <= binary(1);
	hamming_aux(2) <= binary(2);
	-- hamming(3) <= parity3
	hamming_aux(4) <= binary(3);
	-- hamming(5) <= parity2
	-- hamming(6) <= parity1
	
	-- parity determination
	
	parity3 <= hamming_aux(0) xor hamming_aux(1) xor hamming_aux(2);
	
	parity2 <= hamming_aux(4) xor hamming_aux(1) xor hamming_aux(0);
	
	parity1 <= hamming_aux(4) xor hamming_aux(2) xor hamming_aux(0); 
	
	
	-- parity attribution
	
	hamming_aux(3) <= parity3;
	
	hamming_aux(5) <= parity2;
	
	hamming_aux(6) <= parity1;
	
	-- final attribution
	
	hamming <= hamming_aux;
	
end Behaviour;
