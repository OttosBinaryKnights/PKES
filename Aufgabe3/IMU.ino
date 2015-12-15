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

int getOffset(){
  int offset=0;
  for(int i=0;i<30;i++)
    offset += MPU9150_readSensor(MPU9150_GYRO_ZOUT_L, MPU9150_GYRO_ZOUT_H);

  offset /= 30;
  return offset;
}

