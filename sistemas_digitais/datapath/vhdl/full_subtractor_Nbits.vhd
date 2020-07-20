------------------------------------------------------------------------------
-- Full subtractor of N bits
-- Projeto do Datapath - módulo subtrator de N bits
-- Lucas Penna Saraiva e Beatriz Soares Passanezzi
-- Escola Politécnica da USP
-- Ref do circuito: http://www.brainkart.com/article/Full-Subtractor_13556/
-- EX: se A = 0000 0011 e B = 0000 0001, então A-B = 0000 0010
-- EX: se B = 0000 0011 e A = 0000 0001, então B-A = 1111 1110 (que é o complemento de 2 de 0000 0010)
------------------------------------------------------------------------------|

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity full_subtractor_Nbits is

 generic (N_bits: natural := 7); --! Tamanho do subtrator N+1 bits

 Port ( A          : in STD_LOGIC_VECTOR (N_bits downto 0);

        B          : in STD_LOGIC_VECTOR (N_bits downto 0);

        borrow_in  : in STD_LOGIC;

        diff       : out STD_LOGIC_VECTOR (N_bits downto 0);

        borrow_out : out STD_LOGIC);

end full_subtractor_Nbits;


architecture dataflow of full_subtractor_Nbits is

  -- SIGNALS AND COMPONENTS

  signal borrow_aux : STD_LOGIC_VECTOR (N_bits downto 0);
  signal borrow_out_aux : STD_LOGIC;
  signal diff_aux : STD_LOGIC_VECTOR (N_bits downto 0);
  signal A_aux : STD_LOGIC_VECTOR (N_bits downto 0);
  signal B_aux : STD_LOGIC_VECTOR (N_bits downto 0);

  COMPONENT full_subtractor

  Port ( A_i          : in STD_LOGIC;

         B_i          : in STD_LOGIC;

         borrow_in_i  : in STD_LOGIC;

         diff_i       : out STD_LOGIC;

         borrow_out_i : out STD_LOGIC);

  END COMPONENT;

begin

  A_aux <= A;
  B_aux <= B;

   FULL_SUBTRACTOR_NBITS: for n in 0 to N_bits generate

        -- 1 Caso em que é o LSB. Nesse caso, borrow_in é ligado no terra e borrou_out ligado no prox sub
        LSB_SUB: if (n = 0) generate

          lsb_sub : full_subtractor port map (A_aux(n), B_aux(n), borrow_in, diff_aux(n), borrow_aux(n));

        end generate LSB_SUB;

        -- 2 Caso em que é o LSB. Nesse caso, borrow_in sai do sub anterior e borrout_out liga no prox sub
        MEIO_SUB: if ((n /= 0) and (n /= N_bits)) generate -- verificar como fazer essa condição

          meio_sub : full_subtractor port map (A_aux(n), B_aux(n), borrow_aux(n-1), diff_aux(n), borrow_aux(n));

        end generate MEIO_SUB;

        -- 2 Caso em que é o LSB. Nesse caso, borrow_in sai do sub anterior e borrout_out liga no prox sub
        MSB_SUB : if ((n = N_bits) and (n>1)) generate

          msb_sub : full_subtractor port map (A_aux(n), B_aux(n), borrow_aux(n-1), diff_aux(n), borrow_out_aux);

        end generate MSB_SUB;

    end generate FULL_SUBTRACTOR_NBITS;

    borrow_out <= borrow_out_aux;
    diff <= diff_aux;

end dataflow;
