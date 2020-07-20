library IEEE;
use IEEE.NUMERIC_BIT.ALL;


-- Contador de Segundos
entity contador_segundo is
	port (Clock, Clear, Enable: in BIT;
			digit_1, digit_2: out BIT_VECTOR (0 to 6));
end contador_segundo;

architecture Behaviour of contador_segundo is
	
	-- Contador Decimal
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
	
	-- Divisor de clock
	component divisor_clock is
		Port ( Clock          : in BIT;
				Enable         : in BIT;
				Clock_Out      : out BIT);
	end component;	
	
	-- Sinais
	signal Clock_Out: BIT;
	signal rco: BIT;
	signal dig1: BIT_VECTOR (3 downto 0);
	signal dig2: BIT_VECTOR (3 downto 0);
	
begin
	-- Divisão do clock da FPGA para 1 Hz
	contador: divisor_clock port map (Clock, Enable, Clock_Out);

	-- 2 contadores decimais cascateados
	display1: Decade_Counter port map (Clear, Clock_Out,'0', Enable, '1', "0000", rco, dig1);
	display2: Decade_Counter port map (Clear, Clock_Out,'0', rco, '1', "0000", open, dig2);
	
	process (Clock, Clear)
		begin
			
			-- Decodificação para um display de 7 segmentos
			case dig1 is
				when "0000" => digit_1 <= "1111110";
				when "0001" => digit_1 <= "0110000";
				when "0010" => digit_1 <= "1101101";
				when "0011" => digit_1 <= "1111001";
				when "0100" => digit_1 <= "0110011";
				when "0101" => digit_1 <= "1011011";
				when "0110" => digit_1 <= "1011111";
				when "0111" => digit_1 <= "1110000";
				when "1000" => digit_1 <= "1111111";
				when "1001" => digit_1 <= "1110011";
				when others => digit_1 <= "0000000";
			end case;
			
			case dig2 is
				when "0000" => digit_2 <= "1111110";
				when "0001" => digit_2 <= "0110000";
				when "0010" => digit_2 <= "1101101";
				when "0011" => digit_2 <= "1111001";
				when "0100" => digit_2 <= "0110011";
				when "0101" => digit_2 <= "1011011";
				when "0110" => digit_2 <= "1011111";
				when "0111" => digit_2 <= "1110000";
				when "1000" => digit_2 <= "1111111";
				when "1001" => digit_2 <= "1110011";
				when others => digit_1 <= "0000000";
			end case;
			
		end process;
end Behaviour;