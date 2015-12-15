// IMU Register laut: https://cdn.sparkfun.com/datasheets/Sensors/IMU/MPU-9150-Register-Map.pdf


void getIMUangle() {

  double dT = ( (double) MPU9150_readSensor(MPU9150_TEMP_OUT_L, MPU9150_TEMP_OUT_H) + 12412.0) / 340.0;

  // Accelerometer
  double dx = MPU9150_readSensor(MPU9150_ACCEL_XOUT_L, MPU9150_ACCEL_XOUT_H);
  double dy = MPU9150_readSensor(MPU9150_ACCEL_YOUT_L, MPU9150_ACCEL_YOUT_H);
  double dz = MPU9150_readSensor(MPU9150_ACCEL_ZOUT_L, MPU9150_ACCEL_ZOUT_H);

  // Gyro Rates
  //int gx= MPU9150_readSensor(MPU9150_GYRO_XOUT_L, MPU9150_GYRO_XOUT_H);  //not needed
  //int gy= MPU9150_readSensor(MPU9150_GYRO_YOUT_L, MPU9150_GYRO_YOUT_H);  //not needed
  int gz = MPU9150_readSensor(MPU9150_GYRO_ZOUT_L, MPU9150_GYRO_ZOUT_H);

  yangle = atan(dy / sqrt(dx * dx + dz * dz)) * 57.3;
  xangle = atan(dx / sqrt(dx * dx + dz * dz)) * 57.3;

  _delay_ms(100);
}

void IMU_setup() {

  writeSensor( 0x6b, 0u ); //pwermanagement 1

  m_targetAddress = 0x0C;
  writeSensor( 0x0A, 0x00 ); //PowerDownMode
  writeSensor( 0x0A, 0x0F ); //SelfTest
  writeSensor( 0x0A, 0x00 ); //PowerDownMode

  m_targetAddress = 0x69;
  writeSensor( 0x24, 0x40 ); //Wait for Data at Slave0
  writeSensor( 0x25, 0x8C ); //Set i2c address at slave0 at 0x0C
  writeSensor( 0x26, 0x02 ); //Set where reading at slave 0 starts
  writeSensor( 0x27, 0x88 ); //set offset at start reading and enable
  writeSensor( 0x28, 0x0C ); //set i2c address at slv1 at 0x0C
  writeSensor( 0x29, 0x0A ); //Set where reading at slave 1 starts
  writeSensor( 0x2A, 0x81 ); //Enable at set length to 1
  writeSensor( 0x64, 0x01 ); //overvride register
  writeSensor( 0x67, 0x03 ); //set delay rate
  writeSensor( 0x01, 0x80 );

  writeSensor( 0x34, 0x04 ); //set i2c slv4 delay
  writeSensor( 0x64, 0x00 ); //override register
  writeSensor( 0x6A, 0x00 ); //clear usr setting
  writeSensor( 0x64, 0x01 ); //override register
  writeSensor( 0x6A, 0x20 ); //enable master i2c mode
  writeSensor( 0x34, 0x13 ); //disable slv4

  writeSensor( 0x1A, 0x01); //enable 184Hz lowPass filter  Acc & 188Hz Gyro

}

void writeSensor(int addr, int data) {
  Wire.beginTransmission(MPU9150_I2C_ADDRESS);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission(true);
}

int readSensor(int addrL, int addrH) {
  Wire.beginTransmission(MPU9150_I2C_ADDRESS);
  Wire.write(addrL);
  Wire.endTransmission(false);

  Wire.requestFrom(MPU9150_I2C_ADDRESS, 1, true);
  byte L = Wire.read();

  Wire.beginTransmission(MPU9150_I2C_ADDRESS);
  Wire.write(addrH);
  Wire.endTransmission(false);

  Wire.requestFrom(MPU9150_I2C_ADDRESS, 1, true);
  byte H = Wire.read();

  return (H << 8) + L;
}

int getOffset() {
  int offset = 0;
  for (int i = 0; i < 30; i++)
    offset += MPU9150_readSensor(MPU9150_GYRO_ZOUT_L, MPU9150_GYRO_ZOUT_H);

  offset /= 30;
  return offset;
}

double IMU_getOffset() {
  double offset = 0;
  int anz = 100;
  for (int i = 0; i < anz; i++)
    offset += MPU9150_readSensor(MPU9150_GYRO_ZOUT_L, MPU9150_GYRO_ZOUT_H);

  offset /= anz;
  return (int) offset;
}

void IMU_calcHeading() {
  // Erste Messung
  if (IMU_IntTimer != 0)
    IMU_Heading += ((double) micros() - IMU_IntTimer) / 1000000 * (MPU9150_readSensor(MPU9150_GYRO_ZOUT_L, MPU9150_GYRO_ZOUT_H) - IMU_Offset);


  IMU_IntTimer = micros();
}
