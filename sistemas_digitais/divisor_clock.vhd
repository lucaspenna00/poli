-- Escola Politecnica da Universidade de Sao Paulo
-- Laboratorio Digital A - Experiencia 4
--
-- Functional description of 4-bit binary counter on VHDL 
-- 
-- Author: Lucas Penna Saraiva and Stefan R. Raposo
-- 
-- >> Design requirements:
-- 
-- The Clear signal is asynchronous
-- The Load signal is syncrhonous
-- Enable signal

library IEEE;
use IEEE.NUMERIC_BIT.ALL;

entity divisor_clock is

	Port ( Clock          : in BIT;
			 Enable         : in BIT;
			 Clock_Out      : out BIT);

end divisor_clock;



architecture Behaviour of divisor_clock is
	
	component Decade_Counter is

	Port ( Clear          : in BIT;
			 Clock          : in BIT;
			 Load           : in BIT;
			 Enable         : in BIT;
			 Up             : in BIT; -- 'UP = 1 // Down = 0'
			 Counter_Input  : in BIT_VECTOR (3 downto 0);
			 RCO            : out BIT;
			 Counter_Output : out BIT_VECTOR (3 downto 0));

	end component;
	
	component Counter_4_bit is

	Port ( Clear          : in BIT;
			 Clock          : in BIT;
			 Load           : in BIT;
			 Enable         : in BIT;
			 Up             : in BIT; -- 'UP = 1 // Down = 0'
			 Counter_Input  : in BIT_VECTOR (3 downto 0);
			 RCO            : out BIT;
			 Counter_Output : out BIT_VECTOR (3 downto 0));
			 
	end component;
	
	signal rcos : BIT_VECTOR (5 downto 0);
	signal Clear : BIT;
	signal sinal1 : BIT_VECTOR (3 downto 0);
	signal sinal2 : BIT_VECTOR (3 downto 0);
	signal Saidas : BIT_VECTOR (3 downto 0);
	
	
	begin
	
		counter_m5_1: Decade_Counter port map('0', Clock, sinal1(2), '1', '1', "0000", open, sinal1);
		counter_m5_2: Decade_Counter port map('0', Clock,	sinal2(2), sinal1(2), '1', "0000", open, sinal2);
	
		counter1: Decade_Counter port map('0', Clock, '0', sinal1(2) and sinal2(2), '1', "0000", rcos(0), open);
		counter2: Decade_Counter port map('0', Clock, '0', sinal1(2) and sinal2(2) and rcos(0), '1', "0000", rcos(1), open);
		counter3: Decade_Counter port map('0', Clock, '0', sinal1(2) and sinal2(2) and rcos(0) and rcos(1), '1', "0000", rcos(2), open);
		counter4: Decade_Counter port map('0', Clock, '0', sinal1(2) and sinal2(2) and rcos(0) and rcos(1) and rcos(2), '1', "0000", rcos(3), open);
		counter5: Decade_Counter port map('0', Clock, '0', sinal1(2) and sinal2(2) and rcos(0) and rcos(1) and rcos(2) and rcos(3), '1', "0000", rcos(4), open);
		counter6: Decade_Counter port map('0', Clock, '0', sinal1(2) and sinal2(2) and rcos(0) and rcos(1) and rcos(2) and rcos(3) and rcos(4), '1', "0000", rcos(5), open);
		
		
		counter7: Counter_4_bit port map('0', Clock, '0', sinal1(2) and sinal2(2) and rcos(0) and rcos(1) and rcos(2) and rcos(3) and rcos(4) and rcos(5), '1', "0000", open, Saidas);

		Clock_Out <= Saidas(0);
				
	
end Behaviour;