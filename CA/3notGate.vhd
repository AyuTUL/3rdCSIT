library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity NOT_GATE is
	Port
	(
		A : in STD_LOGIC; -- INPUT A
		Y : out STD_LOGIC -- OUTPUT Y
	);
end NOT_GATE;
architecture Behavior of NOT_GATE is begin
	Y <= NOT A;
end Behavior;