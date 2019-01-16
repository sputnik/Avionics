from struct import pack
BNO055_ID = b'\xA0'
BNO055_PAGE_ID_ADDR = b'\x07'

# PAGE0 REGISTER DEFINITION START * /
BNO055_CHIP_ID_ADDR = b'\x00'
BNO055_ACCEL_REV_ID_ADDR = b'\x01'
BNO055_MAG_REV_ID_ADDR = b'\x02'
BNO055_GYRO_REV_ID_ADDR = b'\x03'
BNO055_SW_REV_ID_LSB_ADDR = b'\x04'
BNO055_SW_REV_ID_MSB_ADDR = b'\x05'
BNO055_BL_REV_ID_ADDR = b'\x06'

# Accel data register * /
BNO055_ACCEL_DATA_X_LSB_ADDR = b'\x08'
BNO055_ACCEL_DATA_X_MSB_ADDR = b'\x09'
BNO055_ACCEL_DATA_Y_LSB_ADDR = b'\x0A'
BNO055_ACCEL_DATA_Y_MSB_ADDR = b'\x0B'
BNO055_ACCEL_DATA_Z_LSB_ADDR = b'\x0C'
BNO055_ACCEL_DATA_Z_MSB_ADDR = b'\x0D'

# Mag data register * /
BNO055_MAG_DATA_X_LSB_ADDR = b'\x0E'
BNO055_MAG_DATA_X_MSB_ADDR = b'\x0F'
BNO055_MAG_DATA_Y_LSB_ADDR = b'\x10'
BNO055_MAG_DATA_Y_MSB_ADDR = b'\x11'
BNO055_MAG_DATA_Z_LSB_ADDR = b'\x12'
BNO055_MAG_DATA_Z_MSB_ADDR = b'\x13'

# Gyro data registers * /
BNO055_GYRO_DATA_X_LSB_ADDR = b'\x14'
BNO055_GYRO_DATA_X_MSB_ADDR = b'\x15'
BNO055_GYRO_DATA_Y_LSB_ADDR = b'\x16'
BNO055_GYRO_DATA_Y_MSB_ADDR = b'\x17'
BNO055_GYRO_DATA_Z_LSB_ADDR = b'\x18'
BNO055_GYRO_DATA_Z_MSB_ADDR = b'\x19'

# Euler data registers * /
BNO055_EULER_H_LSB_ADDR = b'\x1A'
BNO055_EULER_H_MSB_ADDR = b'\x1B'
BNO055_EULER_R_LSB_ADDR = b'\x1C'
BNO055_EULER_R_MSB_ADDR = b'\x1D'
BNO055_EULER_P_LSB_ADDR = b'\x1E'
BNO055_EULER_P_MSB_ADDR = b'\x1F'

# Quaternion data registers * /
BNO055_QUATERNION_DATA_W_LSB_ADDR = b'\x20'
BNO055_QUATERNION_DATA_W_MSB_ADDR = b'\x21'
BNO055_QUATERNION_DATA_X_LSB_ADDR = b'\x22'
BNO055_QUATERNION_DATA_X_MSB_ADDR = b'\x23'
BNO055_QUATERNION_DATA_Y_LSB_ADDR = b'\x24'
BNO055_QUATERNION_DATA_Y_MSB_ADDR = b'\x25'
BNO055_QUATERNION_DATA_Z_LSB_ADDR = b'\x26'
BNO055_QUATERNION_DATA_Z_MSB_ADDR = b'\x27'

# Linear acceleration data registers * /
BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR = b'\x28'
BNO055_LINEAR_ACCEL_DATA_X_MSB_ADDR = b'\x29'
BNO055_LINEAR_ACCEL_DATA_Y_LSB_ADDR = b'\x2A'
BNO055_LINEAR_ACCEL_DATA_Y_MSB_ADDR = b'\x2B'
BNO055_LINEAR_ACCEL_DATA_Z_LSB_ADDR = b'\x2C'
BNO055_LINEAR_ACCEL_DATA_Z_MSB_ADDR = b'\x2D'

# Gravity data registers * /
BNO055_GRAVITY_DATA_X_LSB_ADDR = b'\x2E'
BNO055_GRAVITY_DATA_X_MSB_ADDR = b'\x2F'
BNO055_GRAVITY_DATA_Y_LSB_ADDR = b'\x30'
BNO055_GRAVITY_DATA_Y_MSB_ADDR = b'\x31'
BNO055_GRAVITY_DATA_Z_LSB_ADDR = b'\x32'
BNO055_GRAVITY_DATA_Z_MSB_ADDR = b'\x33'

# Temperature data register * /
BNO055_TEMP_ADDR = b'\x34'

# Status registers * /
BNO055_CALIB_STAT_ADDR = b'\x35'
BNO055_SELFTEST_RESULT_ADDR = b'\x36'
BNO055_INTR_STAT_ADDR = b'\x37'

BNO055_SYS_CLK_STAT_ADDR = b'\x38'
BNO055_SYS_STAT_ADDR = b'\x39'
BNO055_SYS_ERR_ADDR = b'\x3A'

# Unit selection register * /
BNO055_UNIT_SEL_ADDR = b'\x3B'
BNO055_DATA_SELECT_ADDR = b'\x3C'

# Mode registers * /
BNO055_OPR_MODE_ADDR = b'\x3D'
BNO055_PWR_MODE_ADDR = b'\x3E'

BNO055_SYS_TRIGGER_ADDR = b'\x3F'
BNO055_TEMP_SOURCE_ADDR = b'\x40'

# Axis remap registers * /
BNO055_AXIS_MAP_CONFIG_ADDR = b'\x41'
BNO055_AXIS_MAP_SIGN_ADDR = b'\x42'

# SIC registers * /
BNO055_SIC_MATRIX_0_LSB_ADDR = b'\x43'
BNO055_SIC_MATRIX_0_MSB_ADDR = b'\x44'
BNO055_SIC_MATRIX_1_LSB_ADDR = b'\x45'
BNO055_SIC_MATRIX_1_MSB_ADDR = b'\x46'
BNO055_SIC_MATRIX_2_LSB_ADDR = b'\x47'
BNO055_SIC_MATRIX_2_MSB_ADDR = b'\x48'
BNO055_SIC_MATRIX_3_LSB_ADDR = b'\x49'
BNO055_SIC_MATRIX_3_MSB_ADDR = b'\x4A'
BNO055_SIC_MATRIX_4_LSB_ADDR = b'\x4B'
BNO055_SIC_MATRIX_4_MSB_ADDR = b'\x4C'
BNO055_SIC_MATRIX_5_LSB_ADDR = b'\x4D'
BNO055_SIC_MATRIX_5_MSB_ADDR = b'\x4E'
BNO055_SIC_MATRIX_6_LSB_ADDR = b'\x4F'
BNO055_SIC_MATRIX_6_MSB_ADDR = b'\x50'
BNO055_SIC_MATRIX_7_LSB_ADDR = b'\x51'
BNO055_SIC_MATRIX_7_MSB_ADDR = b'\x52'
BNO055_SIC_MATRIX_8_LSB_ADDR = b'\x53'
BNO055_SIC_MATRIX_8_MSB_ADDR = b'\x54'

# Accelerometer Offset registers * /
ACCEL_OFFSET_X_LSB_ADDR = b'\x55'
ACCEL_OFFSET_X_MSB_ADDR = b'\x56'
ACCEL_OFFSET_Y_LSB_ADDR = b'\x57'
ACCEL_OFFSET_Y_MSB_ADDR = b'\x58'
ACCEL_OFFSET_Z_LSB_ADDR = b'\x59'
ACCEL_OFFSET_Z_MSB_ADDR = b'\x5A'

# Magnetometer Offset registers * /
MAG_OFFSET_X_LSB_ADDR = b'\x5B'
MAG_OFFSET_X_MSB_ADDR = b'\x5C'
MAG_OFFSET_Y_LSB_ADDR = b'\x5D'
MAG_OFFSET_Y_MSB_ADDR = b'\x5E'
MAG_OFFSET_Z_LSB_ADDR = b'\x5F'
MAG_OFFSET_Z_MSB_ADDR = b'\x60'

# Gyroscope Offset register s * /
GYRO_OFFSET_X_LSB_ADDR = b'\x61'
GYRO_OFFSET_X_MSB_ADDR = b'\x62'
GYRO_OFFSET_Y_LSB_ADDR = b'\x63'
GYRO_OFFSET_Y_MSB_ADDR = b'\x64'
GYRO_OFFSET_Z_LSB_ADDR = b'\x65'
GYRO_OFFSET_Z_MSB_ADDR = b'\x66'

# Radius registers * /
ACCEL_RADIUS_LSB_ADDR = b'\x67'
ACCEL_RADIUS_MSB_ADDR = b'\x68'
MAG_RADIUS_LSB_ADDR = b'\x69'
MAG_RADIUS_MSB_ADDR = b'\x6A'
VECTOR_ACCELEROMETER = BNO055_ACCEL_DATA_X_LSB_ADDR
VECTOR_MAGNETOMETER = BNO055_MAG_DATA_X_LSB_ADDR
VECTOR_GYROSCOPE = BNO055_GYRO_DATA_X_LSB_ADDR
VECTOR_EULER = BNO055_EULER_H_LSB_ADDR
VECTOR_LINEARACCEL = BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR
VECTOR_GRAVITY = BNO055_GRAVITY_DATA_X_LSB_ADDR


class BNO:
   def __init__(self):
      self.x_acc = 0
      self.y_acc = 0
      self.z_acc = 0
      self.x_grav = 0
      self.y_grav = 0
      self.z_grav = 0
   # end def

   def update_values(self, sim):
      self.x_acc = sim.x_acc
      self.y_acc = sim.y_acc
      self.z_acc = sim.z_acc
      self.x_grav = sim.x_grav
      self.y_grav = sim.y_grav
      self.z_grav = sim.z_grav
   # end def

   def deviate_acc(self, val):
      #TODO, placeholder
      return val * 1.05
   # end def

   def receive(self, con):
      data = con.receive(1)
      if data == BNO055_CHIP_ID_ADDR:
         con.send(BNO055_ID)
      elif data == VECTOR_GRAVITY:
         packet = bytearray(pack("<h", round(self.x_grav * 100.0)))
         packet.extend(bytearray(pack("<h", round(self.y_grav * 100.0))))
         packet.extend(bytearray(pack("<h", round(self.z_grav * 100.0))))
         con.send(packet)
      elif data == VECTOR_ACCELEROMETER:
         packet = bytearray(pack("<h", round(self.x_acc * 100)))
         packet.extend(bytearray(pack("<h", round(self.y_acc * 100))))
         packet.extend(bytearray(pack("<h", round(self.z_acc * 100))))
         con.send(packet)
      else:
         print("BNO: Unknown command received: ", data)
   # end def
# end class
