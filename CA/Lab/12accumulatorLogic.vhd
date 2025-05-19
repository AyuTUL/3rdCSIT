library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
entity accumulator_noclk is
    port(
        data_in : in STD_LOGIC_VECTOR(3 downto 0);
        enable  : in STD_LOGIC;
        acc_out : out STD_LOGIC_VECTOR(3 downto 0)
    );
end accumulator_noclk;
architecture Behavioral of accumulator_noclk is
    signal total : unsigned(3 downto 0) := (others => '0');
begin
    process(data_in, enable)
    begin
        if enable = '1' then
            total <= total + unsigned(data_in);
        end if;
    end process;

    acc_out <= std_logic_vector(total);
end Behavioral;
