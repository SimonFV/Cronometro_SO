	component platform is
		port (
			clk_clk                                 : in  std_logic                    := 'X'; -- clk
			reset_reset_n                           : in  std_logic                    := 'X'; -- reset_n
			pio_leds_0_external_connection_export   : out std_logic_vector(9 downto 0);        -- export
			pio_switch_0_external_connection_export : in  std_logic                    := 'X'  -- export
		);
	end component platform;

	u0 : component platform
		port map (
			clk_clk                                 => CONNECTED_TO_clk_clk,                                 --                              clk.clk
			reset_reset_n                           => CONNECTED_TO_reset_reset_n,                           --                            reset.reset_n
			pio_leds_0_external_connection_export   => CONNECTED_TO_pio_leds_0_external_connection_export,   --   pio_leds_0_external_connection.export
			pio_switch_0_external_connection_export => CONNECTED_TO_pio_switch_0_external_connection_export  -- pio_switch_0_external_connection.export
		);

