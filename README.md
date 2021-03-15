# fpga_calculator
This is simple calculator implemented using the [Zybo Z7-10](https://store.digilentinc.com/zybo-z7-zynq-7000-arm-fpga-soc-development-board/) development board's Zynq processor and FPGA. The calculator and add, subtract, multiply, divide, and perform a dot product operations.

The user interacts with the program through a CLI, which passes data to/from the FPGA's digital logic through and AXI4-Lite interface.

Below are diagrams of the device's datapath (Module1Data.vhd) and finite state machine (Module1Controller.vhd) implemented in VHDL:
![Datapath and FSM](https://github.com/jcnoordsij/fpga_calculator/blob/main/diagrams.png?raw=true)
