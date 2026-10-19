
module stack (
    input wire clk,
    input wire reset,
    input wire push,
    input wire pop,
    input wire [15:0] data_in,
    output wire [15:0] data_out,
    output wire empty,
    output wire full
);

    reg [15:0] stack_mem [0:15];
    reg [4:0] sp;

    assign empty = (sp == 0);
    assign full  = (sp == 16);

    // Combinational view of the current top address
    assign data_out = empty ? 16'h0000 : stack_mem[sp - 1'b1];

    always @(posedge clk) begin
        if (reset) begin
            sp <= 0;
        end
        else if (push && !pop && !full) begin
            stack_mem[sp] <= data_in;
            sp <= sp + 1'b1;
        end
        else if (pop && !push && !empty) begin
            sp <= sp - 1'b1;
        end
    end

endmodule
