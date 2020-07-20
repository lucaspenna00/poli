library IEEE;
use IEEE.std_logic_1164.all;
use work.wisdom_package.all;

entity coll_ovf is
	port
	(
	clk			       : in  STD_LOGIC;											--from system
	res				    : in  STD_LOGIC;										   --from system
  disc_addr     : in  STD_LOGIC_VECTOR(7 downto 0);
	ctrl_flags		: out disc_2_base_flags						     	--to control unit
	);

end coll_ovf;

architecture arch of coll_ovf is

--***********************************
--*	INTERNAL SIGNAL DECLARATIONS	*
--***********************************

signal disc_addr_s		  : STD_LOGIC_VECTOR(7 downto 0);
signal ctrl_flags_s     : disc_2_base_flags;

begin

	--*******************************
	--*	SIGNAL ASSIGNMENTS			*
	--*******************************
	disc_addr_s <= disc_addr;

	ctrl_flags_s.end_of_disc <= '1' when disc_addr_s(3) = '1' else '0'; -- verificar se é 3 mesmo
	--ctrl_flags_s.ovf_of_y    <= '1' when disc_addr_s(6) = '1' else '0'; PERGUNTAR AO WANG SE ISSO EH NECESSARIO PRO DISCIPULO!
  ctrl_flags <= ctrl_flags_s;

end arch;
