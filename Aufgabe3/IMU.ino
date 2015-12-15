void getIMUangle() {  
  
  double dT = ( (double) MPU9150_readSensor(MPU9150_TEMP_OUT_L,MPU9150_TEMP_OUT_H) + 12412.0) / 340.0;
  
// Accelerometer
  double dx = MPU9150_readSensor(MPU9150_ACCEL_XOUT_L,MPU9150_ACCEL_XOUT_H);
  double dy = MPU9150_readSensor(MPU9150_ACCEL_YOUT_L,MPU9150_ACCEL_YOUT_H);
  double dz = MPU9150_readSensor(MPU9150_ACCEL_ZOUT_L,MPU9150_ACCEL_ZOUT_H);
        
// Gyro Rates
  //int gx= MPU9150_readSensor(MPU9150_GYRO_XOUT_L, MPU9150_GYRO_XOUT_H);  //not needed
  //int gy= MPU9150_readSensor(MPU9150_GYRO_YOUT_L, MPU9150_GYRO_YOUT_H);  //not needed
  int gz= MPU9150_readSensor(MPU9150_GYRO_ZOUT_L, MPU9150_GYRO_ZOUT_H);

   yangle = atan(dy/sqrt(dx*dx+dz*dz))*57.3;
   xangle = atan(dx/sqrt(dx*dx+dz*dz))*57.3;

  _delay_ms(100);
}

void IMU_setup(){

    MPU9150_I2C_ADDRESS = 0x0C;      //change Address to Compass    

    MPU9150_write(0x0A, 0x00); //PowerDownMode
    MPU9150_write(0x0A, 0x0F); //SelfTest
    MPU9150_write(0x0A, 0x00); //PowerDownMode

    //MPU9150_I2C_ADDRESS = 0x68;      //change Address to MPU
    MPU9150_I2C_ADDRESS = tempAddress; //new version to revert to original address

    MPU9150_write(0x24, 0x40); //Wait for Data at Slave0
    MPU9150_write(0x25, 0x8C); //Set i2c address at slave0 at 0x0C
    MPU9150_write(0x26, 0x02); //Set where reading at slave 0 starts
    MPU9150_write(0x27, 0x88); //set offset at start reading and enable
    MPU9150_write(0x28, 0x0C); //set i2c address at slv1 at 0x0C
    MPU9150_write(0x29, 0x0A); //Set where reading at slave 1 starts
    MPU9150_write(0x2A, 0x81); //Enable at set length to 1
    MPU9150_write(0x64, 0x01); //overvride register
    MPU9150_write(0x67, 0x03); //set delay rate
    MPU9150_write(0x01, 0x80);

    MPU9150_write(0x34, 0x04); //set i2c slv4 delay
    MPU9150_write(0x64, 0x00); //override register
    MPU9150_write(0x6A, 0x00); //clear usr setting
    MPU9150_write(0x64, 0x01); //override register
    MPU9150_write(0x6A, 0x20); //enable master i2c mode
    MPU9150_write(0x34, 0x13); //disable slv4
}

int getOffset(){
  int offset=0;
  for(int i=0;i<30;i++)
    offset += MPU9150_readSensor(MPU9150_GYRO_ZOUT_L, MPU9150_GYRO_ZOUT_H);

  offset /= 30;
  return offset;
}

