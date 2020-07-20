library ieee;
use ieee.std_logic_1164.all;

entity clock_generator is
	generic
	(
	CLK_PERIOD		: TIME	:= 10ns
	);

	port
	(
	clk		: out STD_LOGIC
	);

end clock_generator ;


architecture test of clock_generator is

begin

clk_generation : process

	begin
		CLK <= '1';

		wait for CLK_PERIOD / 2;

		CLK <= '0';

		wait for CLK_PERIOD / 2;

	end process clk_generation;

end architecture test;
