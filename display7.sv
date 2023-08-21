module display7(input logic [3:0] data,
					output logic [6:0] segments);

	always_comb begin
		case(data)
			4'd_0: segments = 7'b1000000;
			4'd_1: segments = 7'b1111001;
			4'd_2: segments = 7'b0100100;
			4'd_3: segments = 7'b0110000;
			4'd_4: segments = 7'b0011001;
			4'd_5: segments = 7'b0010010;
			4'd_6: segments = 7'b0000010;
			4'd_7: segments = 7'b1111000;
			4'd_8: segments = 7'b0000000;
			4'd_9: segments = 7'b0011000;
			default: segments = 7'b1111111;
		endcase
	end
endmodule