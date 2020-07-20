library ieee;

use ieee.std_logic_1164.all;

use ieee.numeric_bit.all;


entity divisor_16666 is
	port(
		clock, enc: in bit;
		sec: out bit);
end divisor_16666;

architecture funcional of divisor_16666 is
	signal contagem: unsigned(14 downto 0):= (others => '0');
	
	signal sec_T: bit:='0';
	

begin

	process (clock, enc, contagem)
	begin
		if (rising_edge(clock) and (enc = '1')) then
			contagem <= contagem + 1;
			if (contagem = "010000010001100") then
				sec_T <= '1';	
			elsif (contagem = "100000100011001") then
				sec_T <= '0';
				contagem <= (others => '0');
			end if;
		end if;
	end process;
	
	
	sec <= sec_T;			
			
end funcional;


		
