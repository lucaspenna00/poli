library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_STD.all;


entity reg is
	generic
	(
	WIDTH	: natural  := 8
	);

	port
	(
	clk  : in  STD_LOGIC;
	clr  : in  STD_LOGIC;
	load : in  STD_LOGIC;
	d    : in  STD_LOGIC_VECTOR(WIDTH-1 downto 0);
	q	  : out STD_LOGIC_VECTOR(WIDTH-1 downto 0)
	);
	
end reg;

architecture arch of reg is

signal q_s	: STD_LOGIC_VECTOR(WIDTH-1 downto 0)	:= (others => '0');

begin

	q <= q_s;

-- Register with active-high clock & asynchronous clear
	process(clk)
	begin
		if clk'EVENT AND clk = '1' then
			if clr = '1' then
				q_s <= (others => '0');
			elsif (load = '1') then
				q_s <= d;
			end if;
		end if;
	end process;

end arch;
