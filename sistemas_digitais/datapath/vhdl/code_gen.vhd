--***************************************************************
--*																*
--*	Title	:													*
--*	Design	:													*
--*	Author	:													*
--*	Email	:													*
--*																*
--***************************************************************
--*																*
--*	Description :												*
--*																*
--***************************************************************
library IEEE;
use IEEE.std_logic_1164.all;
use work.wisdom_package.all;

entity code_gen is
	port
	(
	ctrl_code_sel	: in CODE;
	mem_code_w		: out STD_LOGIC_VECTOR(7 downto 0)
	);
end code_gen;


architecture arch of code_gen is

--***********************************
--*	TYPE & CONSTANTS DECLARATIONS	*
--***********************************

--***********************************
--*	COMPONENT DECLARATIONS			*
--***********************************

--***********************************
--*	INTERNAL SIGNAL DECLARATIONS	*
--***********************************

begin

	--*******************************
	--*	COMPONENT INSTANTIATIONS	*
	--*******************************

	--*******************************
	--*	SIGNAL ASSIGNMENTS			*
	--*******************************

	mem_code_w <= CODE_VECTORS(ctrl_code_sel);


	--*******************************
	--*	PROCESS DEFINITIONS			*
	--*******************************

end arch;
