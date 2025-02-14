library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity OR_GATE is
	Port
	(
		A : in STD_LOGIC; -- INPUT A
		B : in STD_LOGIC; -- INPUT B
		Y : out STD_LOGIC -- OUTPUT Y
	);
end OR_GATE;
architecture Behavior of OR_GATE is begin
	Y <= A OR B;
end Behavior;