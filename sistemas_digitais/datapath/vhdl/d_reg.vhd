library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_STD.all;


entity d_reg is

	generic (t_ff: time := 2 ns);
   
	port
	(
	clk  : in  STD_LOGIC;
	load : in  STD_LOGIC;
	d    : in  STD_LOGIC;
	q	 : out STD_LOGIC
	);
end d_reg;

architecture arch of d_reg is

signal q_s	: STD_LOGIC;

begin

	q <= q_s after t_ff;

-- Register with active-high clock
	process(clk)
	begin
		if clk'EVENT AND clk = '1' then
			if (load = '1') then
				q_s <= d;
			end if;
		end if;
	end process;

end arch;
