-- Polytechnic School of the University of Sao Paulo
-- Digital System and Computer Engineering Department
-- A - Digital Laboratory 
-- Lucas P. Saraiva and Stefan. R. Raposo
-- Exp. 8 ASCII Converter module

library ieee;

use ieee.numeric_bit.all;

entity ASCIIConverter is

	port( rx_output : in  bit_vector(15 downto 0);
			ASCII     : out bit_vector(6  downto 0);
			typeCode  : out bit_vector(4  downto 0)
		);
		

--typeCode(4) HIGH -> means digit
--typeCode(3) HIGH -> means capital letter
--typeCode(2) HIGH -> means ETX
--typeCode(1) HIGH -> means STX
--typeCode(0) HIGH -> means BEL
			
		
end entity;


architecture behaviour of ASCIIConverter is 

	--Component

	component decHamming is
		
		port ( hamming: in bit_vector(6 downto 0);

				 binary: out bit_vector(3 downto 0); 

				 error: out bit 

			  );

	end component;	

	--Signal

	-- less significative Hamming decoder
	
	signal decoderInput1  : bit_vector(6 downto 0);

	signal decoderOutput1 : bit_vector(3 downto 0);
	
	signal error1         : bit;
	
	-- more significative Hamming decoder
	
	signal decoderInput2  : bit_vector(6 downto 0);
	
	signal decoderOutput2 : bit_vector(3 downto 0);
	
	signal error2			 : bit;
	
	signal asciiDecimal   : integer;
	
	--Concatenated word
	
	signal wordToConvert  : bit_vector(7 downto 0);
	
	begin 

	decoder1: decHamming port map(decoderInput1, decoderOutput1, error1);

	decoder2: decHamming port map(decoderInput2, decoderOutput2, error2);
	
	decoderInput2(6) <= rx_output(13);  
	decoderInput2(5) <= rx_output(12);
	decoderInput2(4) <= rx_output(11);	
	decoderInput2(3) <= rx_output(10);
	decoderInput2(2) <= rx_output(9);
	decoderInput2(1) <= rx_output(8);
	decoderInput2(0) <= rx_output(7);

	decoderInput1(6) <= rx_output(6);
	decoderInput1(5) <= rx_output(5);
	decoderInput1(4) <= rx_output(4);
	decoderInput1(3) <= rx_output(3);
	decoderInput1(2) <= rx_output(2);
	decoderInput1(1) <= rx_output(1);
	decoderInput1(0) <= rx_output(0);
	
	wordToConvert(7) <= decoderOutput2(3);
	wordToConvert(6) <= decoderOutput2(2);
	wordToConvert(5) <= decoderOutput2(1);
	wordToConvert(4) <= decoderOutput2(0);
	wordToConvert(3) <= decoderOutput1(3);
	wordToConvert(2) <= decoderOutput1(2);
	wordToConvert(1) <= decoderOutput1(1);
	wordToConvert(0) <= decoderOutput1(0);
	
	asciiDecimal <= to_integer(unsigned(wordToConvert));

	process(asciiDecimal)
	
	begin
	
		if asciiDecimal = 2 then
			
			-- ASCII table: 2 -> STX
		
				typeCode(1) <= '1';
				
				typeCode(2) <= '0';
				typeCode(3) <= '0';
				typeCode(4) <= '0';
				typeCode(0) <= '0';
				
		elsif asciiDecimal = 3 then
		
			-- ASCII table: 3 -> ETX
		
				typeCode(2) <= '1';
				
				typeCode(1) <= '0';
				typeCode(3) <= '0';
				typeCode(4) <= '0';
				typeCode(0) <= '0';
	
		elsif asciiDecimal = 7 then
		
			-- ASCII table: 7 -> BEL
			
				typeCode(0) <= '1';
				
				typeCode(2) <= '0';
				typeCode(3) <= '0';
				typeCode(4) <= '0';
				typeCode(1) <= '0';
				
		elsif asciiDecimal >= 48 and asciiDecimal <= 57 then
		
			-- ASCII table: (from 48 to 57) -> number 0 to 9
	
				typeCode(4) <= '1';

				typeCode(2) <= '0';
				typeCode(3) <= '0';
				typeCode(1) <= '0';
				typeCode(0) <= '0';
	
		elsif asciiDecimal >= 65 and asciiDecimal <= 90 then
		
			-- ASCII table: (from 65 to 90) -> capital letter from A to Z
	
				typeCode(3) <= '1';
				
				typeCode(2) <= '0';
				typeCode(1) <= '0';
				typeCode(4) <= '0';
				typeCode(0) <= '0';		
		
		end if;
		
	end process;

	ASCII(6) <= wordToConvert(6);
	ASCII(5) <= wordToConvert(5);	
	ASCII(4) <= wordToConvert(4);
	ASCII(3) <= wordToConvert(3);
	ASCII(2) <= wordToConvert(2);
	ASCII(1) <= wordToConvert(1);
	ASCII(0) <= wordToConvert(0);
	
end behaviour;