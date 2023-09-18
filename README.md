## Self Balance Robot

This repo serves as a record of my attempt to build a self balance robot.

### Bill of Materials:
- [Node MCU](https://www.ebay.co.uk/itm/263729724888)
- [MPU6050 IMU](https://www.amazon.co.uk/dp/B0957SJL6D?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- [L298N H-Bridge Controller + Motors](https://www.amazon.co.uk/dp/B07ZT5CCFV?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- 9V Battery
- Ribbon Cables
- Custom PCB Board

### Installation
> [!WARNING]  
> Turn off 9V power when connected to Node MCU
1) Download Visual Studio Code
2) Install the [Platform IO Extension](https://platformio.org/)
3) Build `/src/main.cpp` and flash to Node MCU

### Tips on Tuning
- Tuning Parameters found under `/include/control/balance.cpp` are specific to my robot. These may defer if different components are used.
- Typically, the IMU comes with a slight offset that that is specific to each component.

### Future Improvements:
- Mounting holes in PCB board are too small for M3 threads, requires some filing
- Shift wheel motor mounting points closer to the edge
- Over extended periods, wheels does not rotate at magnitudes lower than 0.5 (Due to friction within the motor?)
- Include directional control based on Node MCU's Wifi Module?
  
