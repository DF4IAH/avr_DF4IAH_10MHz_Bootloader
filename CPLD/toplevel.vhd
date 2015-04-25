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
--		TDI 			: in  std_logic;
--		TDO 			: out std_logic;
--		TCK 			: in  std_logic;
--		TMS 			: in  std_logic;


		-- GLOBAL
		RESETn 			: in  std_logic;

		-- Clock Divider
		C_20MHZ 		: in  std_logic;
		C_10MHZ			: out std_logic;
		C_5MHZ			: out std_logic;
		C_2MHZ5			: out std_logic;
		C_1MHZ			: out std_logic;
		C_10KHZ 		: in  std_logic;
		C_PPS			: in  std_logic;

		-- Phase Error Determination
		GPS_REG			: out std_logic;

		SYNC  			: in  std_logic;
		RSFF_CLK		: out std_logic;

		GATE_TRIG		: out std_logic;
		GATE  			: in  std_logic;

		PHASE_RSFF		: out std_logic;
--		PHASE 			: out std_logic;

		-- Serial Communications
		SER_GPS			: in  std_logic;
		ISP_TXD			: in  std_logic;
		ISP_RXD			: out std_logic;
		GPS_RXD			: out std_logic;
		GPS_TXD			: in  std_logic;
		MCU_TXD			: in  std_logic;
		MCU_RXD			: out std_logic;

		-- PWM voltage convertion
		PWM_PULL_IN		: in  std_logic;
		PWM_PULL_OUT		: out std_logic
	);
end;

architecture structural of top_lev is
	component clock_div  -- component declaration for clock_div
		port (
			RESETn		: in  std_logic;
			C_20MHZ		: in  std_logic;
			C_10MHZ		: out std_logic;
			C_5MHZ		: out std_logic;
			C_2MHZ5		: out std_logic;
			C_1MHZ		: out std_logic
		);
	end component;

	component capture  -- component declaration for capture
		port (
			RESETn		: in  std_logic;
--			C_20MHZ		: in  std_logic;
--			C_10MHZ		: in  std_logic;
--			C_5MHZ		: in  std_logic;
			C_2MHZ5		: in  std_logic;
--			C_10KHZ		: in  std_logic;
			C_PPS		: in  std_logic;

			GPS_REG		: out std_logic;

			SYNC		: in  std_logic;
			RSFF_CLK	: out std_logic;

			GATE_TRIG	: out std_logic;
			GATE		: in  std_logic;

			PHASE_RSFF	: out std_logic
--			PHASE		: out std_logic
		);
	end component;

	component sercom  -- component declaration for sercom
		port (
			SER_GPS		: in  std_logic;

			GPS_TXD		: in  std_logic;
			ISP_TXD		: in  std_logic;
			MCU_TXD		: in  std_logic;

			GPS_RXD		: out std_logic;
			ISP_RXD		: out std_logic;
			MCU_RXD		: out std_logic
		);
	end component;


	component pwmpull -- component declaration for pwmpull
		port (
			PWM_PULL_IN	: in  std_logic;
			PWM_PULL_OUT	: out std_logic
		);
	end component;


-- Declaration of top_lev signals
	signal C_10MHZ_loc		:     std_logic;
	signal C_5MHZ_loc		:     std_logic;
	signal C_2MHZ5_loc		:     std_logic;
	signal C_1MHZ_loc		:     std_logic;

begin  --  structural description begins
	clock_div_0: clock_div 
		port map (
			RESETn => RESETn,
			C_20MHZ => C_20MHZ, 
			C_10MHZ => C_10MHZ_loc, 
			C_5MHZ  => C_5MHZ_loc,
			C_2MHZ5 => C_2MHZ5_loc,
			C_1MHZ  => C_1MHZ_loc
		);

	capture_0: capture
		port map (
			RESETn => RESETn,
--			C_20MHZ => C_20MHZ,
--			C_10MHZ => C_10MHZ_loc,
--			C_5MHZ  => C_5MHZ_loc,
			C_2MHZ5 => C_2MHZ5_loc,
--			C_10KHZ => C_10KHZ,
			C_PPS => C_PPS,

			GPS_REG => GPS_REG,

			SYNC => SYNC,
			RSFF_CLK => RSFF_CLK,

			GATE_TRIG => GATE_TRIG,
			GATE => GATE,

			PHASE_RSFF => PHASE_RSFF
--			PHASE => PHASE
		);

	sercom_0 : sercom
		port map (
			SER_GPS => SER_GPS,

			GPS_TXD => GPS_TXD,
			ISP_TXD => ISP_TXD,
			MCU_TXD => MCU_TXD,

			GPS_RXD => GPS_RXD,
			ISP_RXD => ISP_RXD,
			MCU_RXD => MCU_RXD
		);

	pwmpull_0 : pwmpull
		port map (
			PWM_PULL_IN => PWM_PULL_IN,
			PWM_PULL_OUT => PWM_PULL_OUT
		);

	-- OUTPUT pins derived from OUTPUT&INPUT nets
	C_10MHZ <= not C_10MHZ_loc;
	C_5MHZ  <= C_5MHZ_loc;
	C_2MHZ5 <= C_2MHZ5_loc;
	C_1MHZ  <= C_1MHZ_loc;
end structural;


--	-- 8< --

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;

entity clock_div is
	port (
		RESETn			: in  std_logic;
		C_20MHZ			: in  std_logic;
		C_10MHZ			: out std_logic;
		C_5MHZ			: out std_logic;
		C_2MHZ5			: out std_logic;
		C_1MHZ			: out std_logic
	);
end clock_div;

architecture BEHAVIORAL of clock_div is
	signal UINT			: unsigned(2 downto 0);
	signal UINT5			: unsigned(2 downto 0);
	signal LOGCTR			: std_logic_vector(2 downto 0);
	signal C_1MHZ_r			: std_logic;

begin 
	process (RESETn, C_20MHZ)
	begin
	    if RESETn = '0' then
	        UINT <= 0;

	    elsif rising_edge(C_20MHZ) then
	        UINT <= UINT + 1;
	    end if;
	end process;

	process (RESETn, LOGCTR(0))
	begin
	    if RESETn = '0' then
		UINT5 <= 0;
	        C_1MHZ_r <= '0';

	    elsif rising_edge(LOGCTR(0)) then
		if UINT5 = "100" then
			UINT5 <= 0;
			C_1MHZ_r <= not C_1MHZ_r;
		else
		        UINT5 <= UINT5 + 1;
		end if;
	    end if;
	end process;

	LOGCTR  <= std_logic_vector(UINT); -- type conversion
	C_10MHZ <= LOGCTR(0);
	C_5MHZ  <= LOGCTR(1);
	C_2MHZ5 <= LOGCTR(2);
	C_1MHZ	<= C_1MHZ_r;
end BEHAVIORAL;


--	-- 8< --

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;

entity capture is
	port (
		RESETn			: in  std_logic;
--		C_20MHZ			: in  std_logic;
--		C_10MHZ			: in  std_logic;
--		C_5MHZ			: in  std_logic;
		C_2MHZ5			: in  std_logic;
--		C_10KHZ			: in  std_logic;
		C_PPS			: in  std_logic;

		GPS_REG			: out std_logic;

		SYNC			: in  std_logic;
		RSFF_CLK		: out std_logic;

		GATE_TRIG		: out std_logic;
		GATE			: in  std_logic;

		PHASE_RSFF		: out std_logic
--		PHASE			: out std_logic
	);
end capture;

architecture BEHAVIORAL of capture is
signal GPS				:     std_logic;
signal GPSREG_CLK_loc			:     std_logic;
signal RSFF_CLK_loc			:     std_logic;
signal GPS_REG_loc			:     std_logic;
signal PHASE_RSFF_loc			:     std_logic;

begin
	-- async
--	GPS <= C_PPS or C_10KHZ;	-- TODO: remove me! Global pull-down needed
--	GPS <= C_10KHZ;  		-- TODO: remove me!
	GPS <= C_PPS;  			-- TODO: enable me!
	GPSREG_CLK_loc	<= (GPS xor SYNC);
	RSFF_CLK_loc	<= (GPS);

	-- GPS_REG is the registered input of GPS
	process (RESETn, GPSREG_CLK_loc, GPS)
	begin
	    if RESETn = '0' then
		GPS_REG_loc    <= '0';

	    elsif rising_edge(GPSREG_CLK_loc) then
		GPS_REG_loc    <= GPS;
	    end if;
	end process;

	-- Monoflop trigger for GATE signal @ 1PPS
	process (RESETn, GPS)
	begin
	    if RESETn = '0' then
		GATE_TRIG <= '1';

	    else
		GATE_TRIG <= not GPS;
	    end if;
	end process;

	-- Phase determination
	process (RESETn, RSFF_CLK_loc, C_2MHZ5)
	begin
	    if (RESETn = '0') or (C_2MHZ5 = '0') then
		PHASE_RSFF_loc <= '0';

	    elsif rising_edge(RSFF_CLK_loc) then
		PHASE_RSFF_loc <= '1';
	    end if;
	end process;

	-- Output Enable	(not used anymore)
--	process (GATE, PHASE_RSFF_loc)
--	begin
--	    if GATE = '1' then
--		PHASE <= PHASE_RSFF_loc;
--
--	    else
--		PHASE <= 'Z';
--	    end if;
--	end process;

	GPS_REG		<= GPS_REG_loc;
	RSFF_CLK	<= RSFF_CLK_loc;
	PHASE_RSFF	<= PHASE_RSFF_loc;
end BEHAVIORAL;


--	-- 8< --

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity sercom is
	port (
		SER_GPS			: in  std_logic;

		GPS_TXD			: in  std_logic;
		ISP_TXD			: in  std_logic;
		MCU_TXD			: in  std_logic;

		GPS_RXD			: out std_logic;
		ISP_RXD			: out std_logic;
		MCU_RXD			: out std_logic
	);
end sercom;

architecture BEHAVIORAL of sercom is
begin
	process (SER_GPS, GPS_TXD, MCU_TXD, ISP_TXD)
	begin
		if SER_GPS = '1' then
			MCU_RXD <= GPS_TXD;
			GPS_RXD <= MCU_TXD;
			ISP_RXD <= 'Z';
		else
			MCU_RXD <= ISP_TXD;
			ISP_RXD <= MCU_TXD;
			GPS_RXD <= '1';
		end if;
	end process;
end BEHAVIORAL;


--	-- 8< --

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity pwmpull is
	port (
		PWM_PULL_IN		: in  std_logic;
		PWM_PULL_OUT		: out std_logic
	);
end pwmpull;

architecture BEHAVIORAL of pwmpull is
begin
	process (PWM_PULL_IN)
	begin
		PWM_PULL_OUT <= PWM_PULL_IN;
	end process;
end BEHAVIORAL;

