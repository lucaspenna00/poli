entity hamming_error_top_level is

	Port( input_binary:   in bit_vector(3 downto 0);
			
			flip:    		 in bit_vector(2 downto 0);
			
			output_binary:  out bit_vector(3 downto 0);
			
			error_output:   out bit
			
			);

end entity;

architecture Behaviour of hamming_error_top_level is

-- Components

	-- Creating the Hamming Encoder component

	component Hamming_Encoder74 is
	
		port( binary: in bit_vector(3 downto 0);

				hamming: out bit_vector(6 downto 0)
			 );
	
	end component;
	
	-- Creating the Hamming Decoder component

	component decHamming is
	
		port ( hamming: in bit_vector(6 downto 0);
				 
				 binary: out bit_vector(3 downto 0); 
		       
				 error: out bit 
			  
			  );
				 
	end component;
	
-- Signals

	signal hamming: bit_vector(6 downto 0);

	signal hamming_aux: bit_vector(6 downto 0);
	
	
-- Architecture

	begin 
	
	encoder: Hamming_Encoder74 port map(input_binary, hamming);
	
	
	decoder: decHamming port map(hamming_aux, output_binary, error_output);

	
	-- Generating the Hamming Code for the data input
	
	
	
	-- Inversion logic //sequential
	
		hamming_aux(0) <= not(hamming(0)) when flip = "000" else
		hamming(0); 																-- flipping the bits
		
		hamming_aux(1) <= not(hamming(1)) when flip = "001" else	 -- and creating the error
		hamming(1);
		
		hamming_aux(2) <= not(hamming(2)) when flip = "010" else
		hamming(2);
		
		hamming_aux(3) <= not(hamming(3)) when flip = "011" else
		hamming(3);
		
		hamming_aux(4) <= not(hamming(4)) when flip = "100" else
		hamming(4);
		
		hamming_aux(5) <= not(hamming(5)) when flip = "101" else
		hamming(5);
		
		hamming_aux(6) <= not(hamming(6)) when flip = "110" else
		hamming(6);
	
			
end Behaviour;