library ieee;
use IEEE.numeric_bit.all;

entity ascii_toplevel is
	port (
			clock: in bit;
			tx_input : in  bit_vector(6 downto 0);
			ASCII     : out bit_vector(6  downto 0);
			typeCode  : out bit_vector(4  downto 0);
			valid     : out bit;
			reset_L: in bit;
			enable: in bit
		  );
	end entity;

architecture behaviour of ascii_toplevel is
	component ASCIIConverter is
		port (
				rx_output : in  bit_vector(15 downto 0);
				ASCII     : out bit_vector(6  downto 0);
				typeCode  : out bit_vector(4  downto 0)
		     );
		
	end component;
	
	component toplevel is
		port (
			clock: in bit;
			entrada_paralela: in bit_vector (6 downto 0);
			saida_paralela: out bit_vector (15 downto 0);
			enable: in bit
		  );
		
	end component;
	
		signal rx_output: bit_vector (15 downto 0);
		signal type_c: bit_vector(4  downto 0);
		signal ascii_aux: bit_vector(6  downto 0);
		signal valid_aux: bit;
		
	begin
		
		-- Usado para a FPGA
	
		Converter: ASCIIConverter port map (rx_output, ascii_aux, type_c);
		toplevel_communication: toplevel port map (clock, tx_input, rx_output, enable);
		
		valid_aux <= type_c(4) or type_c(3);
		
		valid <= valid_aux;
		
		typeCode <= type_c;
		
		ASCII <= "0000000" when valid_aux = '0' else ascii_aux;
			
		
		
	end behaviour;