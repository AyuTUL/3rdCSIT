library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity NOR_GATE is
	Port
	(
		A : in STD_LOGIC; -- INPUT A
		B : in STD_LOGIC; -- INPUT B
		Y : out STD_LOGIC -- OUTPUT Y
	);
end NOR_GATE;
architecture Behavior of NOR_GATE is begin
	Y <= A NOR B;
end Behavior;
