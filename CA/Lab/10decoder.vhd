library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity decoder_3x8 is
    port (
        A : in  STD_LOGIC_VECTOR (2 downto 0);
        Y : out STD_LOGIC_VECTOR (7 downto 0)
    );
end decoder_3x8;
architecture behavioural of decoder_3x8 is
begin
    process (A)
    begin
        Y <= "00000000";  -- Default output
        case A is
            when "000" => Y <= "00000001";
            when "001" => Y <= "00000010";
            when "010" => Y <= "00000100";
            when "011" => Y <= "00001000";
            when "100" => Y <= "00010000";
            when "101" => Y <= "00100000";
            when "110" => Y <= "01000000";
            when "111" => Y <= "10000000";
            when others => Y <= "00000000";
        end case;
    end process;
end behavioural;

