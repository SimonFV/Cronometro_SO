
module tallernios (
		input  logic	clk, rst_n,
		input logic 	switch,
		output logic [9:0] leds                         
	);
	
	
	platform plat(
		.clk_clk(clk),                          
		.pio_leds_0_external_connection_export(leds),  
		.pio_switch_0_external_connection_export(switch), 
		.reset_reset_n(rst_n)   
	);
	
	
	
endmodule
