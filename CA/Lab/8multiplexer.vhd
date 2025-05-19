library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity mux is
    Port (
        D0 : in  STD_LOGIC;
        D1 : in  STD_LOGIC;
        D2 : in  STD_LOGIC;
        D3 : in  STD_LOGIC;
        S  : in  STD_LOGIC_VECTOR (1 downto 0);
        Y  : out STD_LOGIC
    );
end mux;
architecture Behavioral of mux is
begin
    Y <= D0 when S = "00" else
         D1 when S = "01" else
         D2 when S = "10" else
         D3 when S = "11" else
         '0';
end Behavioral;

