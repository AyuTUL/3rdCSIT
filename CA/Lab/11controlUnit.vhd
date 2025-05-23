library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
entity control_unit is
    Port (
        opcode     : in  STD_LOGIC_VECTOR(1 downto 0);
        ctrl_signal: out STD_LOGIC_VECTOR(1 downto 0)
    );
end control_unit;
architecture Behavioral of control_unit is
begin
    process(opcode)
    begin
        case to_integer(unsigned(opcode)) is
            when 0 => ctrl_signal <= "00";  -- No operation
            when 1 => ctrl_signal <= "01";  -- Load
            when 2 => ctrl_signal <= "10";  -- Store
            when 3 => ctrl_signal <= "11";  -- Add
            when others => ctrl_signal <= "00"; -- Default case
        end case;
    end process;
end Behavioral;

