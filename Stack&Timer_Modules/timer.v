
module timer (
    input wire clk,
    input wire reset,
    input wire load,
    input wire [7:0] load_value,
    input wire tick_60hz,
    output reg [7:0] timer_value
);

    always @(posedge clk) begin
        if (reset) begin
            timer_value <= 8'd0;
        end
        else if (load) begin
            timer_value <= load_value;
        end
        else if (tick_60hz && (timer_value != 0)) begin
            timer_value <= timer_value - 1'b1;
        end
    end

endmodule
