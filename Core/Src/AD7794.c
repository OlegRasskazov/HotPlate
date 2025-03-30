#include "AD7794.h"

static uint8_t Read_8bit(uint8_t REG)
{
  uint8_t TX_Data = Comm_RW | (REG << 3);
  uint8_t RX_Data = 0;
  HAL_SPI_Transmit(&hspi1, &TX_Data, 1, 1000);
  HAL_SPI_Receive(&hspi1, &RX_Data, 1, 1000);
  return RX_Data;
}

static void CheckStatusReady()
{
  uint8_t status;
  bool notready;
  do
  {
    status = Read_8bit(Comm_Reg);
    notready = BIT_IS_SET(status, 7) | !BIT_IS_SET(status, 3) | BIT_IS_SET(status, 5);
    HAL_Delay(100);
  } while (notready);
}

static uint16_t Read_16bit(uint8_t REG)
{
  uint8_t TX_Data = Comm_RW | (REG << 3);
  uint8_t RX_Data[2];
  HAL_SPI_Transmit(&hspi1, &TX_Data, 1, 1000);
  for (uint8_t i = 0; i < 2; i++)
  {
    HAL_SPI_Receive(&hspi1, &RX_Data[i], 1, 1000);
  }
  uint16_t ss = (RX_Data[0] << 8) + (RX_Data[1] << 0);
  return RX_Data;
}

static uint32_t Read_24bit(uint8_t REG)
{
  uint8_t TX_Data = Comm_RW | (REG << 3);
  uint8_t RX_Data[3];
  HAL_SPI_Transmit(&hspi1, &TX_Data, 1, 1000);
  for (uint8_t i = 0; i < 3; i++)
  {
    HAL_SPI_Receive(&hspi1, &RX_Data[i], 1, 1000);
  }
  uint16_t ss = (RX_Data[0] << 16) + (RX_Data[1] << 8) + (RX_Data[2] << 0);
  return RX_Data;
}

static void Write_8bit(uint8_t REG, uint16_t Data)
{
  uint8_t TX_Data = (REG << 3);
  HAL_SPI_Transmit(&hspi1, &TX_Data, 1, 1000);
  HAL_SPI_Transmit(&hspi1, &Data, 1, 1000);
  return;
}

static void Write_16bit(uint8_t REG, uint16_t Data)
{
  uint8_t TX_Data = (REG << 3);
  uint8_t t[2] = {Data >> 8, Data};
  HAL_SPI_Transmit(&hspi1, &TX_Data, 1, 1000);
  for (uint8_t i = 0; i < 2; i++)
  {
    HAL_SPI_Transmit(&hspi1, &t[i], 1, 1000);
  }
  return;
}

static void Write_24bit(uint8_t REG, uint32_t Data)
{
  uint8_t TX_Data = (REG << 3);
  uint8_t RX_Data = reverse_bytes_16(Data);
  HAL_SPI_Transmit(&hspi1, &TX_Data, 1, 1000);
  HAL_SPI_Transmit(&hspi1, &RX_Data, 3, 1000);
}

void SetMode(uint16_t mode)
{
  Write_16bit(Mode_Reg, mode);
}
void SetConfiguration(uint16_t configuration)
{
  Write_16bit(Conf_Reg, configuration);
}
uint32_t ReadMode() { return Read_16bit(Mode_Reg); }
uint16_t ReadConfiguration()
{
  // CheckStatusReady();
  return Read_16bit(Conf_Reg);
}
uint32_t ReadData()
{
  CheckStatusReady();
  return Read_24bit(Data_Reg);
}
