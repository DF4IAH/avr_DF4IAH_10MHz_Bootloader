------------------------------------------------------
-- DF4IAH  10 MHz Ref.-Osc. V2.x - CPLD device
------------------------------------------------------

----------------------------------------
--      Top level
----------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;

entity top_lev is
	port (
--		-- JTAG
--		TDI 		: in  std_logic;
--		TDO 		: out std_logic;
--		TCK 		: in  std_logic;
--		TMS 		: in  std_logic;


		-- GLOBAL
		RESETn 		: in  std_logic;

		-- Clock Divider
		C_20MHZ 	: in  std_logic;
		C_10MHZ		: out std_logic;
		C_10KHZ 	: in  std_logic;
		C_PPS		: in  std_logic;
		C_2MHZ5		: out std_logic;
		
		-- Phase Error Determination
		PPS		: in  std_logic;
		SYNC  		: in  std_logic;
		GATE_TRIG 	: out std_logic;
		GATE  		: in  std_logic;
		PHASE 		: out std_logic;

		-- Serial Communications
		SER_GPS		: in  std_logic;
		ISP_TXD		: in  std_logic;
		ISP_RXD		: out std_logic;
		GPS_RXD		: in  std_logic;
		GPS_TXD		: out std_logic;
		MCU_TXD		: in  std_logic;
		MCU_RXD		: out std_logic
	);
end;

architecture structural of top_lev is
	component clock_div  -- component declaration for clock_div
		port (
			RESETn:	 in  std_logic;
			C_20MHZ: in  std_logic;
			C_10MHZ: out std_logic;
			C_2MHZ5: out std_logic
		);
	end component;

	component capture  -- component declaration for capture
		port (
			RESETn:	  in  std_logic;
			C_10MHZ:  in  std_logic;
--			C_2MHZ5:  in  std_logic;
			C_10KHZ:  in  std_logic;
			C_PPS:	  in  std_logic;
--			SYNC:	  in  std_logic;
			GATE_TRIG: out std_logic;
			GATE: 	  in  std_logic;
			PHASE:	  out std_logic
		);
	end component;

	component sercom  -- component declaration for sercom
		port (
			SER_GPS:  in  std_logic;
			ISP_TXD:  in  std_logic;
			ISP_RXD:  out std_logic;
			GPS_RXD:  in  std_logic;
			GPS_TXD:  out std_logic;
			MCU_TXD:  in  std_logic;
			MCU_RXD:  out std_logic
		);
	end component;

-- Declaration of top_lev signals
signal C_10MHZ_local: std_logic;
signal C_2MHZ5_local: std_logic;

begin  --  structural description begins
	clock_div_0: clock_div 
		port map (
			RESETn => RESETn,
			C_20MHZ => C_20MHZ, 
			C_10MHZ => C_10MHZ_local, 
			C_2MHZ5 => C_2MHZ5_local 
		);

	capture_0: capture
		port map (
			RESETn => RESETn,
			C_10MHZ => C_10MHZ_local,
--			C_2MHZ5 => C_2MHZ5,
			C_10KHZ => C_10KHZ,
			C_PPS => C_PPS,
--			SYNC => SYNC,
			GATE_TRIG => GATE_TRIG,
			GATE => GATE,
			PHASE => PHASE
		);

	sercom_0 : sercom
		port map (
			SER_GPS => SER_GPS,
			ISP_TXD => ISP_TXD,
			ISP_RXD => ISP_RXD,
			GPS_RXD => GPS_RXD,
			GPS_TXD => GPS_TXD,
			MCU_TXD => MCU_TXD,
			MCU_RXD => MCU_RXD
		);

	C_10MHZ <= C_10MHZ_local;
	C_2MHZ5 <= C_2MHZ5_local;
end structural;


--	-- 8< --

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;

entity clock_div is
	port (
		RESETn:	 in  std_logic;
		C_20MHZ: in  std_logic;
		C_10MHZ: out std_logic;
		C_2MHZ5: out std_logic
	);
end clock_div;

architecture BEHAVIORAL of clock_div is
	signal UINT: 	unsigned(2 downto 0);
	signal LOGCTR:	std_logic_vector(2 downto 0);

begin 
	process (C_20MHZ, RESETn)
	begin
	    if RESETn = '0' then
	        UINT <= "000";

	    elsif rising_edge(C_20MHZ) then
	        UINT <= UINT + 1;
	    end if;
	end process;

	LOGCTR <= std_logic_vector(UINT); -- type conversion
	C_10MHZ <= LOGCTR(0);
	C_2MHZ5 <= LOGCTR(2);
end BEHAVIORAL;


--	-- 8< --

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;

entity capture is
	port (
		RESETn:	  in  std_logic;
		C_10MHZ:  in  std_logic;
--		C_2MHZ5:  in  std_logic;
		C_10KHZ:  in  std_logic;
		C_PPS:	  in  std_logic;
--		SYNC:	  in  std_logic;
		GATE_TRIG: out std_logic;
		GATE: 	  in  std_logic;
		PHASE:	  out std_logic
	);
end capture;

architecture BEHAVIORAL of capture is
signal PHASE_JKFF:	std_logic;
signal GPS:		std_logic;

begin
	-- async
	GPS <= C_PPS or C_10KHZ;  -- any high active GPS reference signal is welcome here

	-- Monoflop trigger for Gate signal @ 10 MHz
	process (GPS, RESETn)
	begin
	    if RESETn = '0' then
		GATE_TRIG <= '0';

	    else
		GATE_TRIG <= GPS;
	    end if;
	end process;

	-- Phase determination
	process (GPS, C_10MHZ)
	begin
	    if C_10MHZ = '0' then
		PHASE_JKFF <= '0';

	    elsif rising_edge(GPS) then
		PHASE_JKFF <= '1';
	    end if;
	end process;

	-- Output Enable
	process (PHASE_JKFF, GATE)
	begin
	    if GATE = '1' then
		PHASE <= PHASE_JKFF;

	    else
		PHASE <= 'Z';
	    end if;
	end process;
end BEHAVIORAL;


--	-- 8< --

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity sercom is
	port (
		SER_GPS:  in  std_logic;
		ISP_TXD:  in  std_logic;
		ISP_RXD:  out std_logic;
		GPS_RXD:  in  std_logic;
		GPS_TXD:  out std_logic;
		MCU_TXD:  in  std_logic;
		MCU_RXD:  out std_logic
	);
end sercom;

architecture BEHAVIORAL of sercom is
begin
	process (SER_GPS, GPS_RXD, MCU_TXD)
	begin
		if SER_GPS = '1' then
			MCU_RXD <= GPS_RXD;
			GPS_TXD <= MCU_TXD;
			ISP_RXD <= 'Z';
		else
			MCU_RXD <= ISP_TXD;
			ISP_RXD <= MCU_TXD;
			GPS_TXD <= '1';
		end if;
	end process;
end BEHAVIORAL;

