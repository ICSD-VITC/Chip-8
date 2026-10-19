### Stack and Timer Modules

**Implemented:**
- `stack.v`: A 16-entry stack storing 16-bit return addresses, with push/pop control and empty/full status flags.
- `timer.v`: An 8-bit countdown timer supporting reset, loading an initial value, and decrementing on a 60 Hz tick.

**Instantiation:**
Instantiate the `stack` module in the CPU/control unit to manage subroutine return addresses. Instantiate the `timer` module wherever the CHIP-8 delay timer is managed, connecting `tick_60hz` to a 60 Hz enable signal.

**Status:** Both modules compile successfully using Icarus Verilog. Functional testing and integration are pending.

### Sample Module Instantiation

```verilog
// Stack instance
stack stack_inst (
    .clk(clk),
    .reset(reset),
    .push(stack_push),
    .pop(stack_pop),
    .data_in(return_address),
    .data_out(stack_data_out),
    .empty(stack_empty),
    .full(stack_full)
);

// Delay Timer instance
timer delay_timer_inst (
    .clk(clk),
    .reset(reset),
    .load(timer_load),
    .load_value(timer_load_value),
    .tick_60hz(tick_60hz),
    .timer_value(delay_timer_value)
);
```

**Note:** The signals shown above must be declared and connected in the parent module. These instances demonstrate the intended integration interface; CPU integration and functional testing are pending.
